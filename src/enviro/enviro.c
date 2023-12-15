/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enviro.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 12:20:10 by codespace     #+#    #+#                 */
/*   Updated: 2023/12/15 17:20:55 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	populate_env(t_shell *shell, char **envp);

void	init_env(t_shell *shell, char **envp)
{
	int	count;

	shell->status = SUCCESS;
	count = ft_strarray_count(envp);
	shell->env.envp = ft_calloc(count + 1, sizeof(char *));
	shell->env.envp_name = ft_calloc(count + 1, sizeof(char *));
	shell->env.envp_value = ft_calloc(count + 1, sizeof(char *));
	if (!shell->env.envp || !shell->env.envp_name || !shell->env.envp_value)
		return (update_status(shell, MALLOC_ERROR));
	populate_env(shell, envp);
}

static void	populate_env(t_shell *shell, char **envp)
{
	size_t	i;
	size_t	len;
	char	*val;

	i = 0;
	while (envp && envp[i])
	{
		shell->env.envp[i] = ft_strdup(envp[i]);
		if (!shell->env.envp[i])
			return (update_status(shell, MALLOC_ERROR));
		val = ft_strchr(envp[i], '=');
		if (!val)
			len = ft_strlen(envp[i]);
		else
			len = val - envp[i];
		shell->env.envp_name[i] = ft_substr(envp[i], 0, len);
		if (!shell->env.envp_name[i])
			return (update_status(shell, MALLOC_ERROR));
		if (val)
		{
			val++;
			shell->env.envp_value[i] = ft_strdup(val);
			if (!shell->env.envp_value[i])
				return (update_status(shell, MALLOC_ERROR));
		}
		i++;
	}
	shell->env.count = i;
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
	while (ft_strcmp(shell->env.envp_name[i], name))
		i++;
	if (i < shell->env.count)
		return (shell->env.envp_value[i]);
	return (NULL);
}

void	update_envp(t_shell *shell, char *name, char *value)
{
	int		i;

	i = 0;
	if (!name || !value || !*name || !*value)
		return ;
	while (ft_strcmp(shell->env.envp_name[i], name))
		i++;
	if (i < shell->env.count)
	{
		free(shell->env.envp_value[i]);
		shell->env.envp_value[i] = ft_strdup(value);
		if (!shell->env.envp_value[i])
			return (update_status(shell, MALLOC_ERROR));
		free(shell->env.envp[i]);
		shell->env.envp[i] = ft_joinstrs(3, name, "=", value);
		if (!shell->env.envp[i])
			return (update_status(shell, MALLOC_ERROR));
	}
}

void	clear_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->env.count)
	{
		free(shell->env.envp[i]);
		free(shell->env.envp_name[i]);
		free(shell->env.envp_value[i]);
		i++;
	}
	free(shell->env.envp);
	free(shell->env.envp_name);
	free(shell->env.envp_value);
}
