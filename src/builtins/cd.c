/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:44:57 by dliu          #+#    #+#                 */
/*   Updated: 2023/12/13 15:56:20 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cd_init(t_cd *cd, char **cmd, t_shell *shell);
static void	cd_slash(t_cd *cd);
static void	cd_dot(t_cd *cd);
static void	cd_addpath(t_cd *cd);

void	mini_cd(char **cmd, t_shell *shell)
{
	t_cd	cd;

	update_envp(shell, "OLDPWD", getenvp_value(shell, "PWD"));
	cmd++;
	if (!*cmd)
		return (update_envp(shell, "PWD", getenvp_value(shell, "HOME")));
	cd_init(&cd, cmd, shell);
	while (*cd.cmd)
	{
		if (*cd.cmd == '/')
			cd_slash(&cd);
		else if (*cd.cmd == '.')
			cd_dot(&cd);
		else
			cd_addpath(&cd);
		if (stat(cd.curpath, &cd.statbuf) != 0)
			return (perror("🐢shell: cd: "));
	}
	if (cd.curpath[0])
		update_envp(shell, "PWD", cd.curpath);
}

void	cd_init(t_cd *cd, char **cmd, t_shell *shell)
{
	cd->i = 0;
	cd->cmd = *cmd;
	if (*cd->cmd == '/')
		cd_slash(cd);
	else
	{
		ft_strlcpy(cd->curpath, getenvp_value(shell, "PWD"), PATH_MAX);
		cd->i = ft_strlen(cd->curpath);
	}
}

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
	while (cd->cmd[0] == '.' && cd->cmd[1] == '/')
		cd->cmd += 2;
	while (cd->cmd[0] == '.' && cd->cmd[1] == '.' && cd->cmd[2] == '/')
	{
		while (cd->i > 0 && cd->curpath[cd->i - 1] != '/')
		{
			cd->i--;
			cd->curpath[cd->i] = '\0';
		}
		cd->i--;
		cd->curpath[cd->i] = '\0';
		cd->cmd += 3;
	}
}

static void	cd_addpath(t_cd *cd)
{
	if (cd->curpath[cd->i - 1] != '/')
	{
		cd->curpath[cd->i - 1] = '/';
		cd->i++;
	}
	cd->curpath[cd->i] = '\0';
}