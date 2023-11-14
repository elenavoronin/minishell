/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:51:43 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/14 12:45:30 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include "libft.h"
# include "lifecycle.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

typedef struct s_dummy_cmd
{
	char			*delimiter;
	char			*infile;
	char			*outfile;
	char			output_flag; //append or write (w or a)
	char			**cmd_table;
	t_code_status	status;
}	t_dummy_cmd;

typedef int	t_pipe_fd[2];

typedef struct s_pipes_struct
{
	int				nr_pipes;
	char			*path;
	int				*pid;
	t_pipe_fd		*fd_arr;
}	t_pipes_struct;

void	execute_shell(t_list **cmds, t_shell_state *mini_state);
int		create_pipes(t_list **list, t_pipes_struct *pipes,
			t_shell_state *state);
void	create_children(t_list **list, t_shell_state *mini_state,
			t_pipes_struct *pipes);
void	fork_cmds(char **cmd, int i, t_shell_state *mini_state,
			t_pipes_struct *pipes);
int		create_dummy_cmd(t_list **list);
char	*get_path(char **cmd, char **mini_envp, t_pipes_struct *pipes);
void	close_useless_pipes(int i, t_pipes_struct *pipes);
int		redirect_stuff(int i, t_pipes_struct *pipes);

#endif
