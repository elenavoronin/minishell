/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_b_piping.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:01:17 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/25 13:11:08 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_pipes *pipes, int i)
{
	int	prev;
	int	next;

	if (i == 0)
	{
		close(pipes->fd_arr[0][0]);
		return ;
	}
	while (i < pipes->nr_pipes)
	{
		if (i != prev)
			close(pipes->fd_arr[i][0]);
		if (i != next)
			close(pipes->fd_arr[i][1]);
		i++;
	}
}

int	create_pipes(t_pipes *pipes, t_shell *shell, int nr)
{
	pipes->return_value = 0;
	pipes->nr_pipes = 0;
	pipes->pid = ft_calloc(nr + 1, sizeof(*pipes->pid));
	pipes->path = ft_calloc(nr + 1, sizeof(*pipes->path));
	pipes->infile = ft_calloc(nr + 1, sizeof(*pipes->infile));
	pipes->outfile = ft_calloc(nr + 1, sizeof(*pipes->outfile));
	if (!pipes->pid || !pipes->path || !pipes->infile || !pipes->outfile)
		return (update_status(shell, MALLOC_ERROR));
	if (nr == 0)
		pipes->fd_arr = NULL;
	else
	{
		pipes->fd_arr = ft_calloc(nr, sizeof(*pipes->fd_arr));
		if (!pipes->fd_arr)
			return (update_status(shell, MALLOC_ERROR));
	}
	while (pipes->nr_pipes < nr)
	{
		if (pipe(pipes->fd_arr[pipes->nr_pipes]) != 0)
			return (update_status(shell, INTERNAL_ERROR));
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
	free(pipes->infile);
	free(pipes->outfile);
}
