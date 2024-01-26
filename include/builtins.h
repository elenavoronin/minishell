/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:49 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/26 11:12:42 by dliu          ########   odam.nl         */
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
void	execute_builtins(char **cmd, t_shell *shell);
void	mini_echo(char **cmd);
void	mini_pwd(t_shell *shell);
int		mini_cd(char **cmd, t_shell *shell);
void	mini_env(t_env enviro);
int		mini_export(char **cmd, t_shell *shell);
int		export_check_cmds(char **cmds);
void	mini_unset(char **cmd, t_shell *shell);
void	mini_exit(t_shell *shell);

#endif
