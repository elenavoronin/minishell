/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:51:43 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/25 13:27:29 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef int				t_pipe_fd[2];

typedef struct s_cmd	t_cmd;

typedef struct s_pipes_struct
{
	int				nr_pipes;
	char			**path;
	int				*pid;
	int				*infile;
	int				*outfile;
	int				return_value;
	t_pipe_fd		*fd_arr;
}	t_pipes;

void	execute_shell(t_shell *shell);
int		create_pipes(t_pipes *pipes, t_shell *shell, int nr);
void	get_path(t_shell *shell, t_pipes *pipes);
void	create_children(t_shell *shell, t_pipes *pipes);
void	clear_pipes(t_pipes *pipes, int nr);
void	redirect_input(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i);
void	redirect_output(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i);
int		read_heredoc(t_cmd *cmd);
void	close_pipes(t_pipes *pipes, int cmd_index);

#endif
