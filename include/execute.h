/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 14:51:43 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/11 13:57:56 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef int	t_pipe_fd[2];

typedef struct s_pipes_struct
{
	int				nr_pipes;
	char			**path;
	int				*pid;
	int				return_value;
	t_pipe_fd		*fd_arr;
}	t_pipes;

void	execute_shell(t_list **cmds, t_shell *shell);
int		create_pipes_a(t_list **list, t_pipes *pipes, t_shell *shell, int nr);
int		create_pipes_b(t_list **list, t_pipes *pipes, int nr);
void	create_children(t_list **list, t_shell *shell, t_pipes *pipes);
void	fork_cmds(char **cmd, int i, t_shell *shell, t_pipes *pipes);
char	*get_path_char(char **cmd, char **envp, t_pipes *pipes, int nr);
void	get_path_a(t_list *list, t_pipes *pipes, t_shell *shell);
void	get_path_b(t_list *list, t_pipes *pipes, t_shell *shell);
void	close_useless_pipes(int i, t_pipes *pipes);
void	clear_pipes(t_pipes *pipes, int nr);
void	wait_all(t_pipes *pipes, t_shell *shell);
void	connect_pipes(int i, t_pipes *pipes);
void	redirect_input(t_list **list, t_pipes *pipes, t_shell *shell);
void	redirect_output(t_list **list, t_pipes *pipes, t_shell *shell);

#endif
