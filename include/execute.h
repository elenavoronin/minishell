/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:51:43 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/27 15:24:21 by elenavoroni   ########   odam.nl         */
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
# include <sys/types.h>
# include <sys/wait.h>

typedef int	t_pipe_fd[2];

typedef struct s_pipes_struct
{
	int				nr_pipes;
	char			*path;
	int				*pid;
	t_pipe_fd		*fd_arr;
}	t_pipes_struct;

void	execute_shell(t_list **cmds, t_shell_state *shell_state);
int		create_pipes(t_list **list, t_pipes_struct *pipes,
			t_shell_state *state);
void	create_children(t_list **list, t_shell_state *shell_state,
			t_pipes_struct *pipes);
void	fork_cmds(char **cmd, int i, t_shell_state *shell_state,
			t_pipes_struct *pipes);
char	*get_path_char(char **cmd, char **envp, t_pipes_struct *pipes);
int		get_path(t_list **list, t_pipes_struct *pipes, t_shell_state *state);
void	close_useless_pipes(int i, t_pipes_struct *pipes);
int		redirect_stuff(int i, t_pipes_struct *pipes);
void	clear_pipes(t_pipes_struct *pipes, int nr);
void	wait_all(t_pipes_struct *pipes, t_shell_state *shell_state);
void 	connect_pipes(int i, t_pipes_struct *pipes);

#endif
