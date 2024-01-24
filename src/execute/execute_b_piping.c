/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_b_piping.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:01:17 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/24 12:56:39 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_pipes(t_pipes *pipes, t_shell *shell, int nr)
{
	pipes->return_value = 0;
	pipes->nr_pipes = 0;
	pipes->path = ft_calloc(nr + 1, sizeof(*pipes->path));
	pipes->pid = ft_calloc(nr + 1, sizeof(*pipes->pid));
	pipes->fd_arr = NULL;
	if (!pipes->path || !pipes->pid)
		return (update_status(shell, MALLOC_ERROR));
	if (nr == 0)
		return (SUCCESS);
	pipes->fd_arr = ft_calloc(nr, sizeof(*pipes->fd_arr));
	if (!pipes->fd_arr)
		return (update_status(shell, MALLOC_ERROR));
	while (pipes->nr_pipes < nr)
	{
		if (pipe(pipes->fd_arr[pipes->nr_pipes]) != 0)
		{
			shell->return_value = errno;
			return (update_status(shell, INTERNAL_ERROR));
		}
		pipes->nr_pipes++;
	}
	return (SUCCESS);
}


void	clear_pipes(t_pipes *pipes, int nr)
{
	int	i;

	i = 0;
	while (i <= nr)
	{
		free(pipes->path[i]);
		i++;
	}
	free(pipes->path);
	free(pipes->pid);
	free(pipes->fd_arr);
}
