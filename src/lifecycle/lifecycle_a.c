/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_a.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:58:48 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/03 11:59:02 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_mini_env(t_minienv *minienv)
{
	int		i;
	char	*name;
	char	*path;

	i = 0;
	while (minienv->variable_name[i] != NULL)
	{
		name = minienv->variable_name[i];
		free(name);
		i++;
	}
	i = 0;
	while (minienv->variable_path[i] != NULL)
	{
		path = minienv->variable_path[i];
		free(path);
		i++;
	}
}

void	init_mini_env(t_shell_state *mini_state, char **envp)
{
	int			i;
	t_mini_env	**args;
	char		*name;
	char		*path;

	i = 0;
	mini_state->status_code = 0;
	while (envp[i] != NULL)
	{
		name = 
		path = 
		variable_name[i] = ft_substr(name, sizeof(name));
		variable_path[i] = ft_substr(path, sizeof(path));
		i++;
	}
}

void	start_minishell(int argc, char **argv, char **envp)
{
	char			*line;
	t_shell_state	*mini_status;

	init_mini_env(mini_status, envp);
	while (1)
	{
		line = readline("🐢shell:");
		if (!line)
		{
			rl_clear_history();
			clear_mini_ev(mini_status);
			exit(EXIT_SUCCESS);
		}
		process_line(line);
		add_history(line);
		free(line);
	}
}
