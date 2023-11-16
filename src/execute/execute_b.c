/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_b.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:55:28 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/16 15:16:32 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_char(char **cmd, char **mini_envp, t_pipes_struct *pipes,
			int cmd_nr)
{
	char	**new_paths;
	char	*path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_paths = NULL;
	// if (cmds == builtin ... look in directory, else ... getpath)
	while (mini_envp[i] != NULL)
	{
		if (ft_strnstr(mini_envp[i], "PATH", ft_strlen("PATH")))
		{
			new_paths = ft_split(mini_envp[i], ':');
			if (!new_paths)
				return (NULL);
			break ;
		}
		else
			i++;
	}
	while (new_paths[j] != NULL)
	{
		path = ft_strjoin(new_paths[j], "/");
		if (!path)
		{
			free(new_paths);
			return (NULL);
		}
		pipes->path[cmd_nr] = ft_strjoin(path, cmd[0]);
		if (!pipes->path)
		{
			free(new_paths);
			return (NULL);
		}
		if (access(*pipes->path, X_OK) == 0)
			return (*pipes->path);
		free(path);
		j++;
	}
	// printf("HERE\n");
	// set error code to 127 - command not found and exit
	return (NULL);
}


int	get_path(t_list **list, t_pipes_struct *pipes, t_shell_state *state)
{
	int				nr;
	int				i;
	t_dummy_cmd		*cmds;

	nr = ft_lstsize(*list) - 1;
	i = 0;
	if (nr == 0)
	{
		cmds = (*list)->content;
		pipes->path = malloc(sizeof(char *) );
		if (!pipes->path)
			return (update_status_code(state, MALLOC_ERROR), -1);
		if (get_path_char(cmds->cmd_table, state->mini_env, pipes, i) != 0)
			return (update_status_code(state, INTERNAL_ERROR), -1);
		return (0);
	}
	while (list)
	{
		cmds = (*list)->content;
		pipes->path = malloc(sizeof(char *) * nr);
		if (!pipes->path)
			return (update_status_code(state, MALLOC_ERROR), -1);
		if (!get_path_char(cmds->cmd_table, state->mini_env, pipes, i))
			return (update_status_code(state, PIPE_ERROR), -1);
		*list = (*list)->next;
		i++;
	}
	return (0);
}

int	create_pipes(t_list **list, t_pipes_struct *pipes, t_shell_state *state)
{
	int			nr;
	t_dummy_cmd	*cmds;

	nr = ft_lstsize(*list) - 1;
	while (list)
	{
		cmds = (*list)->content;
		pipes->fd_arr = malloc(sizeof(t_pipe_fd) * (nr + 2));
		if (!pipes->fd_arr)
			return (update_status_code(state, MALLOC_ERROR), -1);
		// pipes->fd_arr[0][0] = STDIN_FILENO;
		// pipes->fd_arr[nr + 1][1] = STDOUT_FILENO;
		if (nr == 0)
			return (0);
		while (pipes->nr_pipes < nr)
		{
			if (pipe(pipes->fd_arr[pipes->nr_pipes + 1]) != 0)
				return (clear_pipes(pipes), -1);
			pipes->nr_pipes++;
		}
		*list = (*list)->next;
	}
	return (0);
}
