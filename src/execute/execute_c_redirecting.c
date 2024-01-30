/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c_redirecting.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/30 15:20:56 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_sgl_builtin(t_cmd *cmd, t_pipes *pipes, t_shell *shell)
{
	pipes->infile[0] = 0;
	pipes->outfile[0] = 1;
	if (cmd->delimiter != NULL)
	{
		pipes->infile[0] = read_heredoc(cmd);
		if (pipes->infile[0] == -1)
		{
			shell->return_value = errno;
			return ;
		}
	}
	if (cmd->infile != NULL)
	{
		pipes->infile[0] = open(cmd->infile, O_RDONLY, 0644);
		if (pipes->infile[0] == -1)
		{
			shell->return_value = 2;
			return ;
		}
	}
	if (cmd->outfile != NULL)
	{
		pipes->outfile[0] = open(cmd->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
}

void	redirect_files(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	if (cmd->delimiter != NULL)
	{
		pipes->infile[i] = read_heredoc(cmd);
		if (pipes->infile[i] == -1)
		{
			shell->return_value = errno;
			return ;
		}
	}
	if (cmd->infile != NULL)
	{
		pipes->infile[i] = open(cmd->infile, O_RDONLY, 0644);
		if (pipes->infile[i] == -1)
		{
			shell->return_value = 2;
			return ;
		}
	}
	if (dup2(pipes->infile[i], STDIN_FILENO) == -1)
	{
		close(pipes->infile[i]);
		shell->return_value = errno;
	}
}

void	redirect_input(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	pipes->infile[i] = STDIN_FILENO;
	if (cmd->infile || cmd->delimiter)
		redirect_files(cmd, pipes, shell, i);
	else if (i != 0)
	{
		pipes->infile[i] = pipes->fd_arr[i - 1][0];
		if (dup2(pipes->infile[i], STDIN_FILENO) == -1)
		{
			close(pipes->infile[i]);
			shell->return_value = errno;
		}
	}
}

void	redirect_output(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	pipes->outfile[i] = STDOUT_FILENO;
	if (cmd->outfile != NULL)
	{
		pipes->outfile[i] = open(cmd->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (pipes->outfile[i] == -1)
		{
			shell->return_value = errno;
			return ;
		}
		if (dup2(pipes->outfile[i], STDOUT_FILENO) == -1)
		{
			shell->return_value = errno;
			close(pipes->outfile[i]);
		}
	}
	else if (i != pipes->nr_pipes)
	{
		pipes->outfile[i] = pipes->fd_arr[i][1];
		if (dup2(pipes->outfile[i], STDOUT_FILENO) == -1)
		{
			shell->return_value = errno;
			close(pipes->outfile[i]);
		}
	}
}
