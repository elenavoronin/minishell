/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/15 11:03:06 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	**copy_enviro(t_shell *shell, char *var_name);

void	mini_unset(char **cmd, t_shell *shell)
{
	int		i;
	char	**new_envp;

	if (!cmd[1] || !*cmd[1])
		return ;
	i = 0;
	while (i < shell->env.count && ft_strcmp(cmd[1], shell->env.envp_name[i]))
		i++;
	if (i == shell->env.count)
		return ;
	new_envp = copy_enviro(shell, cmd[1]);
	if (!new_envp)
	{
		update_status(shell, MALLOC_ERROR);
		return ;
	}
	clear_env(&shell->env);
	if (!init_env(&shell->env, new_envp))
		update_status(shell, MALLOC_ERROR);
	ft_free_strarr(new_envp);
}

static char	**copy_enviro(t_shell *shell, char *var_name)
{
	char	**new_envp;
	int		j;
	int		i;

	new_envp = ft_calloc(shell->env.count, sizeof(*new_envp));
	if (!new_envp)
		return (NULL);
	i = 0;
	j = 0;
	while (i < shell->env.count - 1)
	{
		if (ft_strcmp(shell->env.envp_name[j], var_name))
		{
			new_envp[i] = ft_strdup(shell->env.envp[j]);
			if (!new_envp[i])
			{
				ft_free_strarr(new_envp);
				return (NULL);
			}
			i++;
		}
		j++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}
