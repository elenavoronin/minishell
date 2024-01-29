/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:49 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/29 15:22:02 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <sys/stat.h>
# include <errno.h>

typedef struct s_cd
{
	struct stat	statbuf;
	int			i;
	char		*cmd;
	char		curpath[PATH_MAX];
}	t_cd;

typedef struct s_exp
{
	t_env	cmdenv;
	int		ipos;
	char	**cmd;
	char	**newenvp;
}	t_exp;

int		check_builtins(char **cmd);
void	execute_builtins(char **cmd, t_pipes *pipes, t_shell *shell);
void	mini_echo(char **cmd, int fd);
void	mini_pwd(t_shell *shell, int outfile);
int		mini_cd(char **cmd, t_shell *shell);
void	mini_env(t_env enviro, int fd);
int		mini_export(char **cmd, t_shell *shell, int fd);
int		export_check_cmds(char **cmds);
void	mini_unset(char **cmd, t_shell *shell);
void	mini_exit(t_shell *shell, int fd);

#endif
