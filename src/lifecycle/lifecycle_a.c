/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_a.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:58:48 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/14 11:47:00 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_mini_env(t_shell_state *mini_state)
{
	int			i;
	t_mini_env	**mini_env;
	char		*name;
	char		*path;

	i = 0;
	mini_env = mini_state->mini_env;
	while (mini_env[i])
	{
		name = mini_env[i]->variable_name;
		path = mini_env[i]->variable_path;
		free(name);
		free(path);
		i++;
	}
	free(mini_env);
	free(mini_state);
}

void	update_status_code(t_shell_state *mini_state, t_code_status status)
{
	mini_state->status_code = status;
}

int	mini_env_arr(t_shell_state *mini_state, char **envp)
{
	int		i;
	int		j;

	i = 0;
	while (envp[i] != NULL)
	{
		j = 0;
		mini_state->mini_env[i] = malloc(sizeof(t_mini_env));
		if (!mini_state->mini_env[i])
			return (update_status_code(mini_state, MALLOC_ERROR), -1);
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		mini_state->mini_env[i]->variable_name = ft_substr(envp[i], 0, j);
		if (!mini_state->mini_env[i]->variable_name)
			return (update_status_code(mini_state, MALLOC_ERROR), -1);
		j++;
		mini_state->mini_env[i]->variable_path = ft_strdup(envp[i] + j);
		if (!mini_state->mini_env[i]->variable_path)
			return (update_status_code(mini_state, MALLOC_ERROR), -1);
		i++;
	}
	mini_state->mini_env[i] = NULL;
	return (update_status_code(mini_state, SUCCESS), 0);
}

int	init_mini_state(t_shell_state **mini_state, char **envp)
{
	int			i;

	i = 0;
	(*mini_state) = malloc(sizeof(t_shell_state));
	if (!(*mini_state))
		return (-1);
	(*mini_state)->status_code = 0;
	(*mini_state)->mini_env = malloc(sizeof(t_mini_env *)
			* (count_envp_elements(envp) + 1));
	if (!(*mini_state)->mini_env)
	{
		free(mini_state);
		return (-1);
	}
	if (mini_env_arr(*mini_state, envp) != 0)
	{
		clear_mini_env(*mini_state);
		return (-1);
	}
	return (0);
}

void	start_minishell(int argc, char **argv, char **envp)
{
	// char			*line;
	t_shell_state	*mini_state;
	t_list			*cmds;

	cmds = NULL;
	mini_state = NULL;
	(void)argv;
	(void)argc;
	if (init_mini_state(&mini_state, envp) != 0)
	{
		printf("ERROR\n");
		exit(EXIT_FAILURE);
	}
	// print_env_arr(mini_state->mini_env);
	if (create_dummy_cmd(&cmds) == 0)
		execute_shell(&cmds, mini_state);
	// while (1)
	// {
	// 	line = readline("🐢shell:");
	// 	printf("%s\n", line);
		// if (!line)
		// {
		// 	clear_history();
		// 	clear_mini_env(mini_state);
		// 	exit(EXIT_SUCCESS);
		// }
		// // process_line(line);
		// add_history(line);
		// free(line);
	// }
}
