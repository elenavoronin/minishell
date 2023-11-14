/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:01:17 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/14 19:30:47 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_pipes(int i, t_pipes *pipes)
{
	if (i > 0)
		pipes->fd_arr[i][0] = pipes->fd_arr[i - 1][1];
}

int	redirect_stuff(int i, t_pipes *pipes)
{
	if (i > 0)
	{
		if (pipes->fd_arr[i][0] != STDIN_FILENO)
		{
			if (dup2(pipes->fd_arr[i][0], STDIN_FILENO) == -1)
				return (perror("dup2"), -1);
			close(pipes->fd_arr[i][0]);
		}
	}
	if (i < pipes->nr_pipes)
	{
		if (pipes->fd_arr[i][1] != STDOUT_FILENO)
		{
			if (dup2(pipes->fd_arr[i][1], STDOUT_FILENO) == -1)
				return (perror("dup2"), -1);
			close(pipes->fd_arr[i][1]);
		}
	}
	return (0);
}

void	create_pipes_b(t_list **list, t_pipes *pipes, int nr, t_shell *shell)
{
	t_list	*cmds;

	cmds = (*list);
	while (cmds)
	{
		pipes->return_value = 0;
		if (nr == 0)
		{
			pipes->nr_pipes = 0;
			return ;
		}
		while (pipes->nr_pipes < nr)
		{
			if (pipe(pipes->fd_arr[pipes->nr_pipes + 1]) != 0)
				shell->return_value = errno;
			pipes->nr_pipes++;
		}
		cmds = cmds->next;
	}
}

void	create_pipes_a(t_list **list, t_pipes *pipes, t_shell *shell, int nr)
{
	pipes->pid = malloc(sizeof(int) * (nr + 1));
	if (!pipes->pid)
		shell->return_value = errno;
	pipes->fd_arr = malloc(sizeof(t_pipe_fd) * (nr + 1));
	if (!pipes->fd_arr)
		shell->return_value = errno;
	pipes->path = malloc(sizeof(char *) * (nr + 1));
	if (!pipes->path)
		shell->return_value = errno;
	create_pipes_b(list, pipes, nr, shell);
}
