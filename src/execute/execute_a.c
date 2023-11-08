/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/08 16:59:46 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    execute_shell(t_dummy_cmd *cmds, t_shell_state *mini_state)
{
    t_pipes_struct     pipes;
    
    pipes.nr_pipes = 0;
    if (cmds->nr_pipes > 0)
        create_pipes(cmds, &pipes, mini_state);
    // if (cmds == builtin ... look in directory, else ... getpath)
    create_children(cmds, &pipes, mini_state);
    
}