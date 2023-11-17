/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_b.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 18:41:33 by codespace     #+#    #+#                 */
/*   Updated: 2023/11/17 18:54:19 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_status(t_shell_state *shell_state, t_status code)
{
	shell_state->status = code;
}

void	print_env(const t_shell_state shell_state)
{
	size_t		i;
	const char	**env;

	i = 0;
	env = (const char **)shell_state.env.envp;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	print_env_test(const t_shell_state shell_state)
{
	size_t		i;
	const char	**name;
	const char	**value;

	i = 0;
	name = (const char **)shell_state.env.envp_name;
	value = (const char **)shell_state.env.envp_value;
	while (name[i])
	{
		printf("[%zu][%s]=[%s]\n", i, name[i], value[i]);
		i++;
	}
}
