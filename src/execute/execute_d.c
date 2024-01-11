/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:01:17 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/11 15:18:16 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes_b(t_list **list, t_pipes *pipes, int nr)
{
	t_list	*cmds;

	cmds = (*list);
	while (cmds)
	{
		pipes->return_value = 0;
		if (nr == 0)
		{
			pipes->nr_pipes = 0;
			return (0);
		}
		while (pipes->nr_pipes < nr)
		{
			if (pipe(pipes->fd_arr[pipes->nr_pipes + 1]) != 0)
				return (-1);
			pipes->nr_pipes++;
		}
		cmds = cmds->next;
	}
	return (0);
}

int	create_pipes_a(t_list **list, t_pipes *pipes, t_shell *state, int nr)
{
	t_list	*cmds;

	cmds = (*list);
	pipes->pid = malloc(sizeof(int) * (nr + 1));
	if (!pipes->pid)
		return (update_status(state, MALLOC_ERROR), -1);
	pipes->fd_arr = malloc(sizeof(t_pipe_fd) * (nr + 1));
	if (!pipes->fd_arr)
		return (update_status(state, MALLOC_ERROR), -1);
	pipes->path = malloc(sizeof(char *) * (nr + 1));
	if (!pipes->path)
		return (update_status(state, MALLOC_ERROR), -1);
	return (create_pipes_b(list, pipes, nr));
}
