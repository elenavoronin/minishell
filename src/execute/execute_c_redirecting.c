/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c_redirecting.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/26 14:06:49 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_files(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
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
}

void	redirect_input(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	if (cmd->infile || cmd->delimiter)
	{
		redirect_files(cmd, pipes, shell, i);
		if (shell->return_value != 0)
			return ;
	}
	else
	{
		if (i == 0)
			pipes->infile[i] = dup(STDIN_FILENO);
		else
			pipes->infile[i] = pipes->fd_arr[i - 1][0];
	}
	if (dup2(pipes->infile[i], STDIN_FILENO) == -1)
	{
		close(pipes->infile[i]);
		shell->return_value = errno;
		return ;
	}
	close(pipes->infile[i]);
}

void	redirect_output(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
{
	if (cmd->outfile != NULL)
	{
		pipes->outfile[i] = open(cmd->outfile,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	else
	{
		if (i == pipes->nr_pipes)
			pipes->outfile[i] = dup(STDOUT_FILENO);
		else
			pipes->outfile[i] = pipes->fd_arr[i][1];
	}
	if (dup2(pipes->outfile[i], STDOUT_FILENO) == -1)
	{
		shell->return_value = errno;
		close(pipes->outfile[i]);
		return ;
	}
	close(pipes->outfile[i]);
}


// int	redirect(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i)
// {
// 	redirect_files(cmd, pipes, shell, i);
// 	if (i == 0)
// 	{
// 		if (pipes->infile[i])
// 			dup2(pipes->infile[i], STDIN_FILENO);
// 		close(pipes->fd_arr[0][0]);
// 		if (pipes->outfile[i])
// 			//dup appropriately and close stuff
// 	}
// 	else if (i > 0 && i < pipes->nr_pipes)
// 	{
// 		//probably wrong
// 		if (pipes->infile[i])
// 			dup2(pipes->infile[i], pipes->fd_arr[i][0]);
// 		else
// 			dup2(pipes->fd_arr[i][0], pipes->fd_arr[i - 1][1]);
// 		//close something probably
// 		if (pipes->outfile[i])
// 			//dup appropriately and close stuff
// 	}
// 	else if (i == pipes->nr_pipes)
// 	{
// 		//etc
// 	}
// }
