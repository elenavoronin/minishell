/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c_redirecting.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/18 12:05:56 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	int		fd;

	fd = 0;
	if (cmd->infile != NULL)
	{
		fd = open(cmd->infile, O_RDONLY, 0644);
		if (fd == -1)
		{
			shell->return_value = errno;
			return ;
		}
		pipes->fd_arr[i][0] = fd;
		if (dup2(pipes->fd_arr[i][0], STDIN_FILENO) == -1)
			shell->return_value = errno;
	}
	else
	{
		if (cmd->delimiter != NULL)
			fd = read_heredoc(cmd);
		if (fd == -1)
		{
			shell->return_value = errno;
			return ;
		}
	}
}

void	redirect_output(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	int		fd;

	if (cmd->outfile != NULL)
	{
		fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
		{
			shell->return_value = errno;
			return ;
		}
		pipes->fd_arr[i][1] = fd;
		if (dup2(pipes->fd_arr[i][1], STDOUT_FILENO) == -1)
			shell->return_value = errno;
	}
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
