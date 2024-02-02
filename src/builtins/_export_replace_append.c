/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _export_replace_append.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by dliu          #+#    #+#                 */
/*   Updated: 2024/02/02 06:13:18 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	_count_size(t_shell *shell, t_exp *exp)
{
	exp->size = 0;
	while (exp->size <= shell->env.count)
	{
		if (ft_strcmp(shell->env.envp_name[exp->size], exp->var_name) == 0)
		{
			exp->size = shell->env.count;
			break ;
		}
		exp->size++;
	}
	exp->newenvp = ft_calloc(exp->size + 1, sizeof(*exp->newenvp));
	if (!exp->newenvp)
		return (update_status(shell, MALLOC_ERROR));
	return (SUCCESS);
}

static int	_append(t_shell *shell, t_exp *exp)
{
	if (exp->i < exp->size)
	{
		exp->newenvp[exp->i] = ft_strdup(exp->cmd);
		if (!exp->newenvp[exp->i])
			return (update_status(shell, MALLOC_ERROR));
	}
	return (SUCCESS);
}

int	_replace_and_append(t_shell *shell, t_exp *exp)
{
	if (_count_size(shell, exp) != SUCCESS)
		return (MALLOC_ERROR);
	exp->i = 0;
	while (exp->i < shell->env.count)
	{
		if (ft_strcmp(exp->var_name, shell->env.envp_name[exp->i]) != 0)
		{
			exp->newenvp[exp->i] = ft_strdup(shell->env.envp[exp->i]);
			if (!exp->newenvp[exp->i])
				return (update_status(shell, MALLOC_ERROR));
		}
		else
		{
			exp->newenvp[exp->i] = ft_strdup(exp->cmd);
			if (!exp->newenvp[exp->i])
				return (update_status(shell, MALLOC_ERROR));
		}
		if (!exp->newenvp[exp->i])
		{
			ft_free_strarr(exp->newenvp);
			return (update_status(shell, MALLOC_ERROR));
		}
		exp->i++;
	}
	return (_append(shell, exp));
}
