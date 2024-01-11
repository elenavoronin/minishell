/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:01:17 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/11 17:21:40 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_list	*cmds;

	cmds = (*list);
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
