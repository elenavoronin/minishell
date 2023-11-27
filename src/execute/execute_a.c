/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/27 16:20:18 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(t_pipes_struct *pipes, t_shell_state *shell_state)
{
	int		status;
	int		i;

	i = 0;
	while (pipes->pid[i])
	{
		printf("pipes->pid: %d\n", pipes->pid[i]);
		if (pipes->pid[i] > 0)
			waitpid(pipes->pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		shell_state->return_value = WEXITSTATUS(status);
	else
		shell_state->return_value = 128 + WTERMSIG(status);
}

void	execute_shell(t_list **cmds, t_shell_state *shell_state)
{
	t_pipes_struct	pipes;

	pipes.nr_pipes = 0;
	if (create_pipes(cmds, &pipes, shell_state) != 0)
		update_status(shell_state, INTERNAL_ERROR);
	if (get_path(cmds, &pipes, shell_state) != 0)
		update_status(shell_state, INTERNAL_ERROR);
	create_children(cmds, shell_state, &pipes);
	wait_all(&pipes, shell_state);
	//after each return add cleanup and proper exit
}
