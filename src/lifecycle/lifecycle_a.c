/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_a.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:58:48 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/17 15:45:47 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_shell_state(t_shell_state *shell_state)
{
	int			i;

	i = 0;
	ft_free_strarr(shell_state->env_path_arr);
	free(shell_state->mini_env);
}

void	update_status_code(t_shell_state *shell_state, t_status_code status)
{
	shell_state->status_code = status;
}

int	env_path_arr(t_shell_state *shell_state, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		shell_state->env_path_arr[i] = ft_strdup(envp[i]);
		if (!shell_state->env_path_arr[i])
			return (update_status_code(shell_state, MALLOC_ERROR), -1);
		i++;
	}
	shell_state->env_path_arr[i] = NULL;
	return (0);
}

void	init_shell_state(t_shell_state *shell_state, char **envp)
{
	shell_state->mini_env = malloc(sizeof(t_mini_env **)
			* (count_envp_elements(envp) + 1));
	if (!shell_state->mini_env)
		exit(EXIT_FAILURE);
	shell_state->env_path_arr = (char **)malloc(sizeof(char *)
			* (count_envp_elements(envp) + 1));
	if (!shell_state->env_path_arr)
	{
		clear_shell_state(shell_state);
		exit(EXIT_FAILURE);
	}
	if (env_path_arr(shell_state, envp) != 0)
	{
		clear_shell_state(shell_state);
		exit(EXIT_FAILURE);
	}
	if (env_path_arr_for_printing(shell_state, envp) != 0)
	{
		clear_shell_state(shell_state);
		exit(EXIT_FAILURE);
	}
	shell_state->status_code = 0;
}

void	start_minishell(int argc, char **argv, char **envp)
{
	t_shell_state	shell_state;
	t_list			*cmdlist;
	char			*line;

	cmdlist = NULL;
	(void)argv;
	(void)argc;
	init_shell_state(&shell_state, envp);
	while (1)
	{
		line = readline("🐢shell: ");
		if (!line)
		{
			clear_shell_state(&shell_state);
			clear_history();
			exit(EXIT_SUCCESS);
		}
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		cmdlist = parse_input(line);
		// parse_test(&cmdlist);
		execute_shell(&cmdlist, &shell_state);
		ft_lstclear(&cmdlist, delete_cmd);
		add_history(line);
		free(line);
	}
	clear_shell_state(&shell_state);
}
