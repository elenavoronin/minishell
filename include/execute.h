/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:51:43 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/08 16:48:00 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <fcntl.h>
# include <unistd.h>


typedef struct s_dummy_cmd
{
	char            *delimiter;
	char            *input;
	char            *output;
	char            output_flag;
	char	        **cmd_table;
	t_code_status   status;
    int             nr_pipes;
}	t_dummy_cmd;

typedef int pipe_fd[2];

typedef struct s_pipes_struct
{
    int             nr_pipes;
    pipe_fd         *fd_arr;
}   t_pipes_struct;

void    execute_shell(t_dummy_cmd *cmds, t_shell_state *mini_state);
int     create_pipes(t_dummy_cmd *cmds, t_pipes_struct *pipes,
    t_shell_state *state);

#endif