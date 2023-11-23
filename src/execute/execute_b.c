/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_b.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:55:28 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/23 13:45:49 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_char(char **cmd, char **envp, t_pipes_struct *pipes)
{
	char	**new_paths;
	char	*path;
	int		i;
	int		j;
	

	i = 0;
	j = 0;
	new_paths = NULL;
	// if (ft_strncmp(cmd[0], )
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", ft_strlen("PATH")))
		{
			new_paths = ft_split(envp[i], ':');
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
		pipes->path = ft_strjoin(path, cmd[0]);
		free(path);
		if (!pipes->path)
		{
			free(new_paths);
			return (NULL);
		}
		if (access(pipes->path, X_OK) == 0)
			return (pipes->path);
		j++;
	}
	return (NULL);
}


int	get_path(t_list **list, t_pipes_struct *pipes, t_shell_state *state)
{
	int				i;
	t_cmd			*cmds;

	i = 0;
	if (pipes->nr_pipes == 0)
	{
		cmds = (*list)->content;
		if (get_path_char(cmds->cmd_table, state->env.envp, pipes) == NULL)
			return (update_status(state, INTERNAL_ERROR), -1);
		return (0);
	}
	i = 0;
	while (*list)
	{
		cmds = (*list)->content;
		if (!get_path_char(cmds->cmd_table, state->env.envp, pipes))
			return (update_status(state, PIPE_ERROR), -1);
		*list = (*list)->next;
		i++;
	}
	return (0);
}

int	create_pipes(t_list **list, t_pipes_struct *pipes, t_shell_state *state)
{
	int			nr;
	t_cmd		*cmds;

	nr = ft_lstsize(*list) - 1;
	while (*list)
	{
		cmds = (*list)->content;
		pipes->fd_arr = malloc(sizeof(t_pipe_fd) * (nr + 2));
		if (!pipes->fd_arr)
			return (update_status(state, MALLOC_ERROR), -1);
		pipes->fd_arr[0][0] = STDIN_FILENO;
		pipes->fd_arr[nr + 1][1] = STDOUT_FILENO;
		if (nr == 0)
		{
			pipes->nr_pipes = nr;
			return (0);
		}
		while (pipes->nr_pipes < nr)
		{
			if (pipe(pipes->fd_arr[pipes->nr_pipes + 1]) != 0)
				return (clear_pipes(pipes, pipes->nr_pipes), -1);
			pipes->nr_pipes++;
		}
		*list = (*list)->next;
	}
	return (0);
}
