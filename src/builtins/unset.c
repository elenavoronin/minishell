/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/31 14:19:03 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	**copy_enviro(t_shell *shell, char *var_name);
static int	remove_matching(char *cmd, t_shell *shell);

int	mini_unset(char **cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd[i] && *cmd[i])
	{
		if (remove_matching(cmd[i], shell) != SUCCESS)
		{
			return (shell->status);
		}
		i++;
	}
	return (SUCCESS);
}

static int	remove_matching(char *cmd, t_shell *shell)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (i < shell->env.count && ft_strcmp(cmd, shell->env.envp_name[i]) != 0)
		i++;
	if (i == shell->env.count)
		return (SUCCESS);
	new_envp = copy_enviro(shell, cmd);
	if (!new_envp)
		return (update_status(shell, MALLOC_ERROR));
	clear_env(&shell->env);
	if (init_env(&shell->env, new_envp) != SUCCESS)
		update_status(shell, MALLOC_ERROR);
	ft_free_strarr(new_envp);
	return (shell->status);
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
		if (ft_strcmp(shell->env.envp_name[j], var_name) != 0)
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
