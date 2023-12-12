/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:44:57 by dliu          #+#    #+#                 */
/*   Updated: 2023/12/12 19:44:12 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//WIP on CD
static void	cd_slash(t_cd *cd)
{
	cd->curpath[cd->i] = '/';
	cd->i += 1;
	cd->curpath[cd->i] = '\0';
	while (*cd->cmd == '/')
		cd->cmd++;
}

static void	cd_dot(t_cd *cd)
{
	while (*cd->cmd == '.' && *cd->cmd + 1 == '/')
		cd->cmd += 2;
}

static void	cd_dotdot(t_cd *cd)
{
	struct stat	statbuf;

	if (stat(cd->curpath, &statbuf) == 0)
	{
		cd->cmd += 2;
		while (cd->i >= 0 && cd->curpath[cd->i] != '/')
		{
			cd->curpath[cd->i] = '\0';
			cd->i--;
		}
	}
	else
		perror("🐢shell: cd: ");
	cd->cmd += 3;
}

static void	cd_addpath(t_cd *cd)
{
	cd->curpath[cd->i] = '\0';
}

void	mini_cd(char **cmd, t_shell *shell)
{
	t_cd	cd;

	update_envp(shell, "OLDPWD", getenvp_value(shell, "PWD"));
	cmd++;
	if (!*cmd)
		return (update_envp(shell, "PWD", getenvp_value(shell, "HOME")));
	cd.i = 0;
	cd.cmd = *cmd;
	if (*cd.cmd == '/')
		cd_slash(&cd);
	else
	{
		ft_strlcpy(cd.curpath, getenvp_value(shell, "PWD"), PATH_MAX);
		cd.i = ft_strlen(cd.curpath);
		cd.curpath[cd.i] = '/';
		cd.i++;
	}
	while (*cd.cmd)
	{
		if (*cd.cmd == '/')
			cd_slash(&cd);
		if (*cd.cmd == '.' && *(cd.cmd + 1) == '/')
			cd_dot(&cd);
		if (*cd.cmd == '.' && *(cd.cmd + 1) == '.' && *(cd.cmd + 2) == '/')
			cd_dotdot(&cd);
		else
			cd_addpath(&cd);
	}
	if (cd.curpath[0])
		update_envp(shell, "PWD", cd.curpath);
}
