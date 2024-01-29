/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/29 15:23:08 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*_find_envp(t_env env, t_exp *exp);
static int	_replace_existing(t_exp *exp, t_env oldenv);
static int	_append_new(t_exp *exp);
static void	_export_print(t_env env, int fd);

int	mini_export(char **cmd, t_shell *shell, int fd)
{
	t_exp	exp;

	if (cmd[1] && *cmd[1])
	{
		if (export_check_cmds(cmd + 1) != SUCCESS)
			return (update_status(shell, SYNTAX_ERROR));
		exp.newenvp = ft_calloc(ft_strarray_count(cmd) + shell->env.count,
				sizeof(*exp.newenvp));
		if (!exp.newenvp)
			return (update_status(shell, MALLOC_ERROR));
		exp.cmd = cmd + 1;
		if (_replace_existing(&exp, shell->env) != SUCCESS)
			return (update_status(shell, MALLOC_ERROR));
		if (_append_new(&exp) != SUCCESS)
			return (update_status(shell, MALLOC_ERROR));
		clear_env(&exp.cmdenv);
		clear_env(&shell->env);
		init_env(&shell->env, exp.newenvp);
		ft_free_strarr(exp.newenvp);
	}
	else
		_export_print(shell->env, fd);
	return (SUCCESS);
}

static int	_replace_existing(t_exp *exp, t_env oldenv)
{
	if (init_env(&exp->cmdenv, exp->cmd) != SUCCESS)
		return (ft_free_strarr(exp->newenvp), MALLOC_ERROR);
	exp->ipos = 0;
	while (oldenv.envp[exp->ipos])
	{
		exp->newenvp[exp->ipos] = _find_envp(oldenv, exp);
		if (!exp->newenvp[exp->ipos])
		{
			ft_free_strarr(exp->newenvp);
			return (clear_env(&exp->cmdenv), MALLOC_ERROR);
		}
		exp->ipos++;
	}
	return (SUCCESS);
}

static int	_append_new(t_exp *exp)
{
	int	i;

	i = 0;
	while (i < exp->cmdenv.count)
	{
		if (exp->cmdenv.envp_name[i])
		{
			exp->newenvp[exp->ipos] = ft_strdup(exp->cmdenv.envp[i]);
			if (!exp->newenvp[exp->ipos])
			{
				ft_free_strarr(exp->newenvp);
				exp->newenvp = NULL;
				clear_env(&exp->cmdenv);
				return (MALLOC_ERROR);
			}
			exp->ipos++;
		}
		i++;
	}
	return (SUCCESS);
}

static char	*_find_envp(t_env env, t_exp *exp)
{
	int	i;

	i = 0;
	while (i < exp->cmdenv.count)
	{
		if (ft_strcmp(env.envp_name[exp->ipos], exp->cmdenv.envp_name[i]) == 0)
			break ;
		i++;
	}
	if (i < exp->cmdenv.count)
	{
		free(exp->cmdenv.envp_name[i]);
		exp->cmdenv.envp_name[i] = NULL;
		return (ft_strdup(exp->cmdenv.envp[i]));
	}
	else
		return (ft_strdup(env.envp[exp->ipos]));
}

static void	_export_print(t_env env, int fd)
{
	int	i;

	i = 0;
	while (env.envp[i])
	{
		ft_putstr_fd(env.envp_name[i], fd);
		if (env.envp_value[i])
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(env.envp_value[i], fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
}
