/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_a.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:58:48 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/14 14:53:38 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_mini_env(t_shell_state *mini_state)
{
	int			i;

	i = 0;
	while (mini_state->mini_env[i])
	{
		free(mini_state->mini_env[i]);
		i++;
	}
	free(mini_state->mini_env);
	free(mini_state);
}

void	update_status_code(t_shell_state *mini_state, t_code_status status)
{
	mini_state->status_code = status;
}

// int	mini_env_arr_for_printing(t_shell_state *mini_state, char **envp)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (envp[i] != NULL)
// 	{
// 		j = 0;
// 		mini_state->mini_env[i] = malloc(sizeof(t_mini_env));
// 		if (!mini_state->mini_env[i])
// 			return (update_status_code(mini_state, MALLOC_ERROR), -1);
// 		while (envp[i][j] && envp[i][j] != '=')
// 			j++;
// 		mini_state->mini_env[i]->variable_name = ft_substr(envp[i], 0, j);
// 		if (!mini_state->mini_env[i]->variable_name)
// 			return (update_status_code(mini_state, MALLOC_ERROR), -1);
// 		j++;
// 		mini_state->mini_env[i]->variable_path = ft_strdup(envp[i] + j);
// 		if (!mini_state->mini_env[i]->variable_path)
// 			return (update_status_code(mini_state, MALLOC_ERROR), -1);
// 		i++;
// 	}
// 	mini_state->mini_env[i] = NULL;
// 	return (update_status_code(mini_state, SUCCESS), 0);
// }

int	mini_env_arr(t_shell_state *mini_state, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		mini_state->mini_env[i] = ft_strdup(envp[i]);
		if (!mini_state->mini_env[i])
			return (update_status_code(mini_state, MALLOC_ERROR), -1);
		i++;
	}
	mini_state->mini_env[i] = NULL;
	return (0);
}

int	init_mini_state(t_shell_state **mini_state, char **envp)
{
	// int	i;

	// i = 0;
	(*mini_state) = malloc(sizeof(t_shell_state));
	if (!(*mini_state))
		return (-1);
	(*mini_state)->status_code = 0;
	(*mini_state)->mini_env = (char **)malloc(sizeof(char *)
			* (count_envp_elements(envp) + 1));
	if (!(*mini_state)->mini_env)
		return (-1);
	if (mini_env_arr(*mini_state, envp) != 0)
	{
		clear_mini_env(*mini_state);
		return (-1);
	}
	return (0);
}

void	start_minishell(int argc, char **argv, char **envp)
{
	t_shell_state	*mini_state;
	t_list			*cmdlist;
	char			*line;

	cmdlist = NULL;
	mini_state = NULL;
	(void)argv;
	(void)argc;
	if (init_mini_state(&mini_state, envp) != 0)
	{
		printf("ERROR\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("🐢shell: ");
		if (!line)
		{
			clear_history();
			clear_mini_env(mini_state);
			exit(EXIT_SUCCESS);
		}
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		cmdlist = parse_input(line);
		parse_test(&cmdlist);
		// execute_shell(&cmdlist, mini_state);
		ft_lstclear(&cmdlist, delete_cmd);
		add_history(line);
		free(line);
	}
}
