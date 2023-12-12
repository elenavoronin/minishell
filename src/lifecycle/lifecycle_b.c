/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_b.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: codespace <codespace@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/17 18:41:33 by codespace     #+#    #+#                 */
/*   Updated: 2023/12/12 13:27:58 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_status(t_shell_state *shell_state, t_status code)
{
	shell_state->status = code;
}

/**
 * Searches through env array by name and returns pointer to
 * corresponding envp_value, or NULL if not found.
 * 
 * Note: Does NOT allocate new memory, so do not free!
*/
char	*getenvp_value(t_shell_state *shell_state, char *name)
{
	int		i;

	i = 0;
	while (shell_state->env.envp_name[i]
		&& ft_strcmp(shell_state->env.envp_name[i], name))
		i++;
	if (ft_strcmp(shell_state->env.envp_name[i], name) == 0)
		return (shell_state->env.envp_value[i]);
	return (NULL);
}

void	test_print_env(const t_shell_state shell_state)
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
