/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_b.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:55:28 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/08 16:59:51 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clean_pipes(t_pipes_struct *pipes)
{
    int i;

    i = 0;
    free(pipes->fd_arr);
        
}

int   create_pipes(t_dummy_cmd *cmds, t_pipes_struct *pipes,
    t_shell_state *state)
{
    pipes->fd_arr = malloc(sizeof(pipe_fd) * (cmds->nr_pipes + 2));
    if (!pipes->fd_arr)
        return(update_status_code(state, MALLOC_ERROR), -1);
    pipes->fd_arr[0][0] = STDIN_FILENO;
    pipes->fd_arr[0][1] = STDOUT_FILENO;
    while (pipes->nr_pipes < cmds->nr_pipes)
    {
        if (pipe(pipes->fd_arr[pipes->nr_pipes + 1]) != 0)
            return(clean_pipes(&pipes), -1);
        pipes->nr_pipes++; 
    }
    return (0);
}