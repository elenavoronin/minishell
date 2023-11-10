/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_a.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:58:48 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/10 09:37:23 by elenavoroni   ########   odam.nl         */
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

void	mini_env_arr(t_shell_state *mini_state, char **envp, char *name, char *path)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		name = ft_substr(envp[i], 0, j);
		if (!name)
			return(update_status_code(mini_state, MALLOC_ERROR));
		j++;
		path = ft_strdup(envp[i] + j);
		if (!path)
			return(update_status_code(mini_state, MALLOC_ERROR));
		mini_state->mini_env[i] = malloc(sizeof(t_mini_env));
		if (!mini_state->mini_env[i])
			return(update_status_code(mini_state, MALLOC_ERROR));
		mini_state->mini_env[i]->variable_name = name;
		mini_state->mini_env[i]->variable_path = path;
		i++;
	}
	mini_state->status_code = SUCCESS;
}

void	init_mini_state(t_shell_state *mini_state, char **envp)
{
	int			i;
	char		*name;
	char		*path;

	i = 0;
	name = NULL;
	path = NULL;
	mini_state = ft_calloc(1, sizeof(t_shell_state));
	if (!mini_state)
		return ;
	mini_state->status_code = 0;
	mini_state->mini_env = malloc(sizeof(t_mini_env **)
		* count_envp_elements(envp));
	if (!mini_state->mini_env)
	{
		mini_state->status_code = MALLOC_ERROR;
		return ;
	}
	mini_env_arr(mini_state, envp, name, path);
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
	init_mini_state(mini_state, envp);
	if (create_dummy_cmd(cmds) == 0)
		execute_shell(cmds, mini_state);
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
