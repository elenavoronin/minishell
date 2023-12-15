/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/15 17:17:23 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	export_var(char **cmd, t_shell *shell)
{
	char **new_env;
	int	i;

	i = ft_strarray_count(cmd) + shell->env.count;
	new_env = ft_calloc(i, sizeof(*new_env));
	if (!new_env)
		return (update_status(shell, MALLOC_ERROR));
	i = 0;
	while (i < shell->env.count)
	{
		new_env[i] = ft_strdup(shell->env.envp[i]);
		if (!new_env[i])
		{
			ft_free_strarr(new_env);
			return (update_status(shell, MALLOC_ERROR));
		}
		i++;
	}
	cmd++;
	while (*cmd)
	{
		new_env[i] = ft_strdup(*cmd);
		if (!new_env[i])
		{
			ft_free_strarr(new_env);
			return (update_status(shell, MALLOC_ERROR));
		}
		cmd++;
		i++;
	}
	new_env[i] = NULL;
	clear_env(shell);
	init_env(shell, new_env);
	ft_free_strarr(new_env);
}

void	mini_export(char **cmd, t_shell *shell)
{
	// char **sorted_envp;

	if (cmd[1])
		export_var(cmd, shell);
	// else
	// {
	// 	sorted_envp = sort_env(shell);
	// 	if (!sorted_envp)
	// 		return ;
	// 	declare_x(sorted_envp);
	// }
}
