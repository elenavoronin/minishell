/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_b_piping.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 12:01:17 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/23 17:48:01 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_pipes *pipes, int i)
{
	int	prev;
	int	next;

	if (i == 0)
		return ;
	prev = i - 1;
	next = i;
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
	pipes->nr_pipes = 0;
	pipes->return_value = 0;
	pipes->infile = ft_calloc(nr + 1, sizeof(*pipes->infile));
	pipes->outfile = ft_calloc(nr + 1, sizeof(*pipes->outfile));
	pipes->pid = ft_calloc(nr + 1, sizeof(*pipes->pid));
	pipes->fd_arr = ft_calloc(nr, sizeof(*pipes->fd_arr));
	pipes->path = ft_calloc(nr + 1, sizeof(*pipes->path));
	if (!pipes->path || !pipes->fd_arr || !pipes->path
		|| !pipes->infile || !pipes->outfile)
	{
		shell->return_value = errno;
		return (update_status(shell, MALLOC_ERROR));
	}
	if (nr == 0)
		return (SUCCESS);
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
