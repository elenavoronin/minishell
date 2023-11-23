/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/23 16:36:15 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_all(t_pipes_struct *pipes)
{
	int		status;
	int		i;

	i = 0;
	while (pipes->pid[i])
	{
		if (pipes->pid[i] > 0)
			waitpid(pipes->pid[i], &status, 0);
		i++;
	}
	return (status);
}

int	execute_shell(t_list **cmds, t_shell_state *shell_state)
{
	t_pipes_struct	pipes;
	int				retcode;

	pipes.nr_pipes = 0;
	if (create_pipes(cmds, &pipes, shell_state) != 0)
		return (update_status(shell_state, INTERNAL_ERROR), -1);
	if (get_path(cmds, &pipes, shell_state) != 0)
		return (update_status(shell_state, INTERNAL_ERROR), -1);
	create_children(cmds, shell_state, &pipes);
	retcode = wait_all(&pipes);
	return (retcode);
	// if (WIFEXITED(status))
	// 	exit(WEXITSTATUS(status));
	//after each return add cleanup and proper exit
	// proper_exit_code() exit codes should match bash + use the status code for this
}
