/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by dliu          #+#    #+#                 */
/*   Updated: 2024/02/01 12:50:03 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	_export_print(t_env env, int fd);
static int	_validate_and_getname(t_shell *shell, t_exp *exp, char **cmd);
static void	_clear_exp(t_exp *exp);

static void	_clear_exp(t_exp *exp)
{
	exp->i = 0;
	ft_free_strarr(exp->newenvp);
	exp->newenvp = NULL;
	free(exp->var_name);
	exp->var_name = NULL;
}

int	mini_export(char **cmd, t_shell *shell, int fd)
{
	t_exp	exp;
	int		i;

	ft_bzero(&exp, sizeof(exp));
	i = 1;
	if (cmd && cmd[i])
	{
		while (cmd[i])
		{
			_clear_exp(&exp);
			if (_validate_and_getname(shell, &exp, &cmd[i]) == SUCCESS)
			{
				if (_replace_and_append(shell, &exp) != SUCCESS)
					break ;
				clear_env(&shell->env);
				init_env(&shell->env, exp.newenvp);
			}
			i++;
		}
		_clear_exp(&exp);
		return (shell->return_value);
	}
	_export_print(shell->env, fd);
	return (shell->return_value);
}

static int	_validate_and_getname(t_shell *shell, t_exp *exp, char **cmd)
{
	int	i;

	i = 0;
	exp->cmd = *cmd;
	if (!ft_isalpha(exp->cmd[i]) && exp->cmd[i] != '_')
	{
		ft_perror("🐢shell: export", exp->cmd, "not a valid identifier");
		shell->return_value = SYNTAX_ERROR;
		return (update_status(shell, SYNTAX_ERROR));
	}
	while (exp->cmd[i] && exp->cmd[i] != '=')
	{
		if (!ft_isalnum(exp->cmd[i]) && exp->cmd[i] != '_')
		{
			ft_perror("🐢shell: export", exp->cmd, "not a valid identifier");
			shell->return_value = SYNTAX_ERROR;
			return (update_status(shell, SYNTAX_ERROR));
		}
		i++;
	}
	exp->var_name = ft_substr(exp->cmd, 0, i);
	if (!exp->var_name)
		return (update_status(shell, MALLOC_ERROR));
	return (SUCCESS);
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
