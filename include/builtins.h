/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:49 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/23 15:32:37 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
// # include <linux/limits.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_cd
{
	struct stat	statbuf;
	int			i;
	char		*cmd;
	char		curpath[PATH_MAX];
}	t_cd;

int		check_builtins(char **cmd);
void	execute_builtins(char **cmd, t_shell *shell);
void	mini_echo(char **cmd);
void	mini_pwd(t_shell *shell);
void	mini_cd(char **cmd, t_shell *shell);
void	mini_env(t_env enviro);
void	mini_export(char **cmd, t_shell *shell);
void	mini_unset(char **cmd, t_shell *shell);
void	mini_exit(t_shell *shell);

#endif
