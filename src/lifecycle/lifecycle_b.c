/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_b.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 17:12:21 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/16 12:22:23 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envp_elements(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	return (count);
}

void	print_env_arr(char **mini_env)
{
	int	i;

	i = 0;
	while (mini_env[i] != NULL)
	{
		printf("[%d]: %s\n", i, mini_env[i]);
		i++;
	}
}

int	mini_env_arr_for_printing(t_shell_state *mini_state, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		mini_state->env_pathv[i] = malloc(sizeof(t_mini_env));
		if (!mini_state->env_pathv[i])
			return (update_status_code(mini_state, MALLOC_ERROR), -1);
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		mini_state->env_pathv[i]->variable_name = ft_substr(envp[i], 0, j);
		if (!mini_state->env_pathv[i]->variable_name)
			return (update_status_code(mini_state, MALLOC_ERROR), -1);
		j++;
		mini_state->env_pathv[i]->variable_path = ft_strdup(envp[i] + j);
		if (!mini_state->env_pathv[i]->variable_path)
			return (update_status_code(mini_state, MALLOC_ERROR), -1);
		i++;
	}
	return (update_status_code(mini_state, SUCCESS), 0);
}
