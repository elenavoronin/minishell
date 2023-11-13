/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_b.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:55:28 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/13 17:01:56 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clean_pipes(t_pipes_struct *pipes)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (pipes->fd_arr)
	{
		free(pipes->fd_arr[i]);
		i++;
	}
	free(pipes->path);
	free(pipes->pid);
	free(pipes);
}

char	*get_path(char **cmd, t_mini_env **mini_envp, t_pipes_struct *pipes)
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
		if (ft_strnstr(mini_envp[i]->variable_name, "PATH", ft_strlen("PATH")))
		{
			new_paths = ft_split(mini_envp[i]->variable_path, ':');
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
		if (!pipes->path)
		{
			free(new_paths);
			return (NULL);
		}
		if (access(pipes->path, X_OK) == 0)
			return (pipes->path);
		free(path);
		free(pipes->path);
		j++;
	}
	// printf("HERE\n");
	// set error code to 127 - command not found and exit
	return (NULL);
}

int	create_pipes(t_list **list, t_pipes_struct *pipes, t_shell_state *state)
{
	int			nr;
	t_dummy_cmd	*cmds;

	while (list)
	{
		cmds = (*list)->content;
		nr = ft_lstsize(*list) - 1;
		pipes->fd_arr = malloc(sizeof(t_pipe_fd) * (nr + 2));
		if (!pipes->fd_arr)
			return (update_status_code(state, MALLOC_ERROR), -1);
		pipes->fd_arr[0][0] = STDIN_FILENO;
		pipes->fd_arr[nr + 1][1] = STDOUT_FILENO;
		if (nr <= 0) // if i don't have pipes, I need to call execve directly
		{
			if (!get_path(cmds->cmd_table, state->mini_env, pipes))
				return (update_status_code(state, INTERNAL_ERROR), -1);
			return (0);
		}
		while (pipes->nr_pipes < nr)
		{
			if (pipe(pipes->fd_arr[pipes->nr_pipes + 1]) != 0)
				return (clean_pipes(pipes), -1);
			pipes->nr_pipes++;
		}
		if (!get_path(cmds->cmd_table, state->mini_env, pipes))
			return (update_status_code(state, PIPE_ERROR), -1);
		pipes->pid = malloc(sizeof(int) * pipes->nr_pipes);
		if (!pipes->pid)
			return (clean_pipes(pipes), -1);
		*list = (*list)->next;
	}
	return (0);
}
