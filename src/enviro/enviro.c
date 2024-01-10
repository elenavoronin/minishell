/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enviro.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 12:20:10 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/10 12:52:10 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	populate_env(t_env *env, char **envp);

int	init_env(t_env *env, char **envp)
{
	env->count = ft_strarray_count(envp);
	env->envp = ft_calloc(env->count + 1, sizeof(char *));
	env->envp_name = ft_calloc(env->count + 1, sizeof(char *));
	env->envp_value = ft_calloc(env->count + 1, sizeof(char *));
	if (!env->envp || !env->envp_name || !env->envp_value)
		return (0);
	if (!populate_env(env, envp))
		return (0);
	return (1);
}

static int	populate_env(t_env *env, char **envp)
{
	int		i;
	size_t	len;
	char	*val;

	i = 0;
	while (envp && envp[i])
	{
		val = ft_strchr(envp[i], '=');
		if (!val)
			len = ft_strlen(envp[i]);
		else
			len = val - envp[i];
		env->envp_name[i] = ft_substr(envp[i], 0, len);
		if (!env->envp_name[i])
			return (0);
		if (val)
			val++;
		if (!update_envp(env, env->envp_name[i], val))
			return (0);
		i++;
	}
	env->count = i;
	return (1);
}

/**
 * Searches through env array by name and returns pointer to
 * corresponding envp_value, or NULL if not found.
 * 
 * Note: Does NOT allocate new memory, so do not free!
*/
char	*getenvp_value(t_env *env, char *name)
{
	int	i;

	if (!name)
		return (NULL);
	i = 0;
	while (ft_strcmp(env->envp_name[i], name))
		i++;
	if (i < env->count)
		return (env->envp_value[i]);
	return (NULL);
}

/**
 * Update environent variable
 * @param name The name of the variable to update
 * @param value The new value of the variable
 * Automatically creates new envp value by joining the name and value with '='
 * @return 1 if successful, 0 if there is a malloc error.
 * Remember to update the status in shell.
*/
int	update_envp(t_env *env, char *name, char *value)
{
	int		i;

	i = 0;
	while (ft_strcmp(env->envp_name[i], name))
		i++;
	if (i < env->count)
	{
		free(env->envp_value[i]);
		free(env->envp[i]);
		if (value)
		{
			env->envp_value[i] = ft_strdup(value);
			env->envp[i] = ft_joinstrs(3, name, "=", value);
		}
		else
		{
			env->envp_value[i] = NULL;
			env->envp[i] = ft_strdup(name);
		}
		if (!env->envp[i])
			return (0);
	}
	return (1);
}

void	clear_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		free(env->envp[i]);
		free(env->envp_name[i]);
		free(env->envp_value[i]);
		i++;
	}
	free(env->envp);
	free(env->envp_name);
	free(env->envp_value);
}
