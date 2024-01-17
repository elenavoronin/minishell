/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:51:43 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/17 14:21:00 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "parse.h"
# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef int	t_pipe_fd[2];

typedef struct s_cmd t_cmd;

typedef struct s_pipes_struct
{
	int				nr_pipes;
	char			**path;
	int				*pid;
	int				return_value;
	t_pipe_fd		*fd_arr;
}	t_pipes;

void	execute_shell(t_list **cmds, t_shell *shell);
void	create_pipes_a(t_list **list, t_pipes *pipes, t_shell *shell, int nr);
void	create_pipes_b(t_list **list, t_pipes *pipes, int nr, t_shell *shell);
void	create_children(t_list **list, t_shell *shell, t_pipes *pipes);
void	fork_cmds(t_list *list, int i, t_shell *shell, t_pipes *pipes);
char	*get_path_char(char **cmd, char **envp, t_pipes *pipes, int nr);
void	get_path_a(t_list *list, t_pipes *pipes, t_shell *shell);
void	get_path_b(t_list *list, t_pipes *pipes, t_shell *shell);
void	close_useless_pipes(int i, t_pipes *pipes);
void	clear_pipes(t_pipes *pipes, int nr);
void	wait_all(t_pipes *pipes, t_shell *shell);
void	connect_pipes(int i, t_pipes *pipes);
int		redirect_stuff(int i, t_pipes *pipes);
void	redirect_input(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i);
void	redirect_output(t_cmd *cmd, t_pipes *pipes, t_shell *shell, int i);
void	execute_children(t_list *list, t_shell *shell, t_pipes *pipes);
int		read_heredoc(t_cmd *cmd);

#endif
