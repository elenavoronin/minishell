/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_a.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:58:48 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/03 16:46:42 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	print_env_arr(t_mini_env **mini_env)
{
	int	i;

	i = 0;
	while (mini_env[i] != NULL)
	{
		printf("[%d]: %s\n", i, mini_env[i]->variable_name);
		printf("[%d]: %s\n", i,  mini_env[i]->variable_path);
		i++;
	}
}


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

void	init_mini_state(t_shell_state *mini_state, char **envp)
{
	int			i;
	int			j;
	char		*name;
	char		*path;

	i = 0;
	mini_state = ft_calloc(1, sizeof(t_shell_state));
	if (!mini_state)
		return ;
	mini_state->status_code = 0;
	mini_state->mini_env = ft_calloc(1, sizeof(t_mini_env *));
	if (!mini_state->mini_env)
	{
		mini_state->status_code = MALLOC_ERROR;
		return ;
	}
	while (envp[i] != NULL)
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		name = ft_substr(envp[i], 0, i);
		if (!name)
		{
			mini_state->status_code = MALLOC_ERROR;
			return ;
		}
		j++;
		path = ft_strdup(envp[i] + j + 1);
		if (!path)
		{
			mini_state->status_code = MALLOC_ERROR;
			return ;
		}
		mini_state->mini_env[i] = ft_calloc(1, sizeof(t_mini_env));
		if (!mini_state->mini_env[i])
		{
			mini_state->status_code = MALLOC_ERROR;
			break ;
		}
		mini_state->mini_env[i]->variable_name = name;
		mini_state->mini_env[i]->variable_path = path;
		i++;
	}
	mini_state->status_code = SUCCESS;
	print_env_arr(mini_state->mini_env);
}

void	start_minishell(int argc, char **argv, char **envp)
{
	// char			*line;
	t_shell_state	*mini_state;

	mini_state = NULL;
	(void)argv;
	(void)argc;
	init_mini_state(mini_state, envp);
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
