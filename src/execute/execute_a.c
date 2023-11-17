/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/17 15:09:03 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_shell(t_list **cmds, t_shell_state *shell_state)
{
	t_pipes_struct	pipes;

	pipes.nr_pipes = 0;
	if (create_pipes(cmds, &pipes, shell_state) != 0)
		return ;
	if (get_path(cmds, &pipes, shell_state) != 0)
		return ;
	create_children(cmds, shell_state, &pipes);
	//after each return add cleanup and proper exit
	// proper_exit_code() exit codes should match bash + use the status code for this
}
