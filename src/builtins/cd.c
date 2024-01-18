/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:44:57 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/18 11:56:35 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	_setcurpath(t_cd *cd, char **cmd, t_shell *shell);
static void	_slash(t_cd *cd);
static void	_dot(t_cd *cd);
static void	_appendpath(t_cd *cd);

int	mini_cd(char **cmd, t_shell *shell)
{
	t_cd	cd;

	if (ft_strarray_count(cmd) > 2)
		return (ft_perror("🐢shell", "cd", "too many arguments"),
			update_status(shell, SYNTAX_ERROR));
	if (update_envp(&shell->env, "OLDPWD", getenv_value(shell->env, "PWD"), 0) != SUCCESS)
		return (update_status(shell, MALLOC_ERROR));
	cmd++;
	if (!*cmd)
	{
		if (update_envp(&shell->env, "PWD", getenv_value(shell->env, "HOME"), 0) != SUCCESS)
			return (update_status(shell, MALLOC_ERROR));
		if (chdir(getenv_value(shell->env, "HOME")) < 0)
			return (perror("🐢shell: cd"), update_status(shell, INTERNAL_ERROR));
		return (SUCCESS);
	}
	if (!_setcurpath(&cd, cmd, shell))
		return (perror("🐢shell: cd"), update_status(shell, INTERNAL_ERROR));
	if (update_envp(&shell->env, "PWD", cd.curpath, 0) != SUCCESS)
		return (update_status(shell, MALLOC_ERROR));
	chdir(cd.curpath);
	return (SUCCESS);
}

static int	_setcurpath(t_cd *cd, char **cmd, t_shell *shell)
{
	cd->i = 0;
	cd->cmd = *cmd;
	if (*cd->cmd == '/')
		_slash(cd);
	else
	{
		ft_strlcpy(cd->curpath, getenv_value(shell->env, "PWD"), PATH_MAX);
		cd->i = ft_strlen(cd->curpath);
	}
	while (*cd->cmd && cd->i < PATH_MAX)
	{
		if (*cd->cmd == '/')
			_slash(cd);
		else if (*cd->cmd == '.')
			_dot(cd);
		else
			_appendpath(cd);
		if (stat(cd->curpath, &cd->statbuf) != 0)
			return (0);
	}
	return (1);
}

static void	_slash(t_cd *cd)
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

static void	_dot(t_cd *cd)
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

static void	_appendpath(t_cd *cd)
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
