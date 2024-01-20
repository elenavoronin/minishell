/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c_redirecting.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/20 13:16:29 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	if (dup2(pipes->fd_arr[i][0], STDIN_FILENO) == -1)
		shell->return_value = errno;
	if (cmd->delimiter != NULL)
	{
		pipes->fd_arr[i][0] = read_heredoc(cmd);
		if (pipes->fd_arr[i][0] == -1)
		{
			shell->return_value = errno;
			return ;
		}
	}
	if (dup2(pipes->fd_arr[i][0], STDIN_FILENO) == -1)
		shell->return_value = errno;
	close(pipes->fd_arr[i][0]);
	if (cmd->infile != NULL)
	{
		pipes->fd_arr[i][0] = open(cmd->infile, O_RDONLY, 0644);
		if (pipes->fd_arr[i][0] == -1)
		{
			shell->return_value = errno;
			return ;
		}
	}
	close(pipes->fd_arr[i][1]);
}

void	redirect_output(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	if (cmd->outfile != NULL)
	{
		pipes->fd_arr[i][1] = open(cmd->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipes->fd_arr[i][1] == -1)
		{
			shell->return_value = errno;
			return ;
		}
		if (dup2(pipes->fd_arr[i][1], STDOUT_FILENO) == -1)
			shell->return_value = errno;
	}
	close(pipes->fd_arr[i][1]);
}

int	redirect_stuff(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	redirect_input(cmd, pipes, shell, i);
	if (i > 0 && i < pipes->nr_pipes)
	{
		pipes->fd_arr[i + 1][0] = pipes->fd_arr[i][1];
		redirect_output(cmd, pipes, shell, i);
	}
	if (i == pipes->nr_pipes && i != 0)
	{
		if (dup2(pipes->fd_arr[i][0], STDIN_FILENO) == -1)
			return (perror("dup2"), -1);
		close(pipes->fd_arr[i][0]);
	}
	return (0);
}
