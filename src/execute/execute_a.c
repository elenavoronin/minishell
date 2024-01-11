/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/11 12:05:41 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(t_pipes *pipes, t_shell *shell)
{
	int		status;
	int		i;

	i = 0;
	while (i < pipes->nr_pipes)
	{
		if (pipes->pid[i] > 0)
			waitpid(pipes->pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		shell->return_value = WEXITSTATUS(status);
	else
		shell->return_value = 128 + WTERMSIG(status);
}

void	execute_shell(t_list **cmds, t_shell *shell)
{
	int		nr;
	t_pipes	pipes;

	pipes.nr_pipes = 0;
	nr = ft_lstsize(*cmds) - 1;
	if (create_pipes_a(cmds, &pipes, shell, nr) != 0)
	{
		update_status(shell, INTERNAL_ERROR);
		return ;
	}
	if (get_path_a(*cmds, &pipes, shell) != 0)
	{
		update_status(shell, INTERNAL_ERROR);
		return ;
	}
	if ((redirect_input(cmds, &pipes) != 0)
		|| (redirect_output(cmds, &pipes) != 0))
	{
		update_status(shell, INTERNAL_ERROR);
		return ;
	}
	create_children(cmds, shell, &pipes);
	wait_all(&pipes, shell);
}
