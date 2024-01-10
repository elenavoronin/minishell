/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/10 12:39:26 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	find_var(char *name, t_shell *shell);
static char	**copy_enviro(int var, t_shell *shell);

void	mini_unset(char **cmd, t_shell *shell)
{
	char	**new_envp;
	int		var;

	var = find_var(cmd[1], shell);
	if (var < 0)
		return ;
	new_envp = copy_enviro(var, shell);
	if (!new_envp)
		return (update_status(shell, MALLOC_ERROR));
	clear_env(&shell->env);
	init_env(&shell->env, new_envp);
	ft_free_strarr(new_envp);
}

static int	find_var(char *name, t_shell *shell)
{
	int	var;

	if (!name)
		return (-1);
	var = 0;
	while (ft_strcmp(shell->env.envp_name[var], name))
		var++;
	if (var < shell->env.count)
		return (var);
	return (-1);
}

static char	**copy_enviro(int var, t_shell *shell)
{
	char	**new_envp;
	char	**old_envp;
	int		i;

	old_envp = shell->env.envp;
	new_envp = ft_calloc(ft_strarray_count(old_envp), sizeof(*new_envp));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (*old_envp)
	{
		if (i != var)
		{
			new_envp[i] = ft_strdup(*old_envp);
			if (!new_envp[i])
			{
				ft_free_strarr(new_envp);
				return (NULL);
			}
			i++;
		}
		old_envp++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
