/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/19 10:02:45 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(t_pipes *pipes, t_shell *shell)
{
	int		status;
	int		i;

	i = 0;
	while (i <= pipes->nr_pipes)
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
	if (create_pipes(cmds, &pipes, shell, nr) != 0)
		update_status(shell, INTERNAL_ERROR);
	if (get_path(cmds, &pipes, shell) != 0)
		update_status(shell, INTERNAL_ERROR);
	if (redirect_input(cmds, &pipes) != 0)
		update_status(shell, INTERNAL_ERROR);
	if (redirect_output(cmds, &pipes) != 0)
		update_status(shell, INTERNAL_ERROR);
	create_children(cmds, shell, &pipes);
	wait_all(&pipes, shell);
	//after each return add cleanup and proper exit
}
