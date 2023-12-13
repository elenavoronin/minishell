/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:49 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/13 15:55:27 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
# include <linux/limits.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_cd
{
	struct stat	statbuf;
	char		*cmd;
	char		curpath[PATH_MAX];
	int			i;
}	t_cd;

int		check_builtins(char **cmd);
void	execute_builtins(char **cmd, t_shell *shell);
void	mini_env(t_env env);
void	mini_echo(char **cmd);
void	mini_pwd(t_shell *shell);
void	mini_cd(char **cmd, t_shell *shell);
void	mini_exit(t_shell *shell);

#endif
