/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_b.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 17:12:21 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/17 15:43:17 by elenavoroni   ########   odam.nl         */
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

void	print_env_arr(char **env_path_arr)
{
	int	i;

	i = 0;
	while (env_path_arr[i] != NULL)
	{
		printf("[%d]: %s\n", i, env_path_arr[i]);
		i++;
	}
}

int	env_path_arr_for_printing(t_shell_state *shell_state, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		shell_state->mini_env = malloc(sizeof(t_mini_env)
				* (count_envp_elements(envp) + 1));
		if (!shell_state->mini_env)
		{
			clear_shell_state(shell_state);
			exit(EXIT_FAILURE);
		}
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		shell_state->mini_env[i].variable_name = ft_substr(envp[i], 0, j);
		if (!shell_state->mini_env[i].variable_name)
		{
			clear_shell_state(shell_state);
			exit(EXIT_FAILURE);
		}
		j++;
		shell_state->mini_env[i].variable_path = ft_strdup(envp[i] + j);
		if (!shell_state->mini_env[i].variable_path)
		{
			clear_shell_state(shell_state);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	shell_state->mini_env[i].variable_name = NULL;
	shell_state->mini_env[i].variable_path = NULL;
	return (update_status_code(shell_state, SUCCESS), 0);
}
