/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:44:57 by dliu          #+#    #+#                 */
/*   Updated: 2023/12/17 16:10:44 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	cd_init(t_cd *cd, char **cmd, t_shell *shell);
static void	cd_slash(t_cd *cd);
static void	cd_dot(t_cd *cd);
static void	cd_appendpath(t_cd *cd);

void	mini_cd(char **cmd, t_shell *shell)
{
	t_cd	cd;

	if (ft_strarray_count(cmd) > 2)
	{
		ft_perror("🐢shell", "cd", "too many arguments");
		return (update_status(shell, SYNTAX_ERROR));
	}
	update_envp(shell, "OLDPWD", getenvp_value(shell, "PWD"));
	if (shell->status != SUCCESS)
		return ;
	cmd++;
	if (!*cmd)
		return (update_envp(shell, "PWD", getenvp_value(shell, "HOME")));
	cd_init(&cd, cmd, shell);
	while (*cd.cmd && cd.i < PATH_MAX)
	{
		if (*cd.cmd == '/')
			cd_slash(&cd);
		else if (*cd.cmd == '.')
			cd_dot(&cd);
		else
			cd_appendpath(&cd);
		if (stat(cd.curpath, &cd.statbuf) != 0)
			return (perror("🐢shell: cd"));
	}
	update_envp(shell, "PWD", cd.curpath);
	if (shell->status != SUCCESS)
		return ;
	chdir(cd.curpath);
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
	while (*cd->cmd == '/')
		cd->cmd++;
	if (*cd->cmd && cd->curpath[cd->i - 1] != '/')
	{
		cd->curpath[cd->i] = '/';
		cd->i += 1;
		cd->curpath[cd->i] = '\0';
	}
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
		if (cd->curpath[cd->i - 1] == '/' && cd->i > 1)
		{
			cd->i--;
			cd->curpath[cd->i] = '\0';
		}
		cd->cmd += 3;
	}
}

static void	cd_appendpath(t_cd *cd)
{
	int	i;

	i = 0;
	if (cd->curpath[cd->i - 1] != '/')
	{
		cd->curpath[cd->i] = '/';
		cd->i++;
	}
	while (cd->cmd[i] && cd->cmd[i] != '/')
	{
		cd->curpath[cd->i] = cd->cmd[i];
		cd->i++;
		cd->curpath[cd->i] = '\0';
		i++;
	}
	cd->curpath[cd->i] = '\0';
	cd->cmd += i;
}
