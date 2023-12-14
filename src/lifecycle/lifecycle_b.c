/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_b.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 18:41:33 by codespace     #+#    #+#                 */
/*   Updated: 2023/12/12 18:15:26 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_status(t_shell *shell, t_status code)
{
	shell->status = code;
}

/**
 * Searches through env array by name and returns pointer to
 * corresponding envp_value, or NULL if not found.
 * 
 * Note: Does NOT allocate new memory, so do not free!
*/
char	*getenvp_value(t_shell *shell, char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (NULL);
	while (shell->env.envp_name[i]
		&& ft_strcmp(shell->env.envp_name[i], name))
		i++;
	if (ft_strcmp(shell->env.envp_name[i], name) == 0)
		return (shell->env.envp_value[i]);
	return (NULL);
}

void	update_envp(t_shell *shell, char *name, char *value)
{
	int	i;

	i = 0;
	if (!name || !value)
		return ;
	while (shell->env.envp_name[i]
		&& ft_strcmp(shell->env.envp_name[i], name))
		i++;
	if (ft_strcmp(shell->env.envp_name[i], name) == 0)
	{
		free(shell->env.envp_value[i]);
		shell->env.envp_value[i] = ft_strdup(value);
		free(shell->env.envp[i]);
		shell->env.envp[i] = ft_joinstrs(3, shell->env.envp_name, "=", value);
	}
}
