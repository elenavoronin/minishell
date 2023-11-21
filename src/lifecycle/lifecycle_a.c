/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_a.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:58:48 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/21 15:44:46 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell_state(t_shell_state *shell_state, char **envp);
static int	populate_shell_state(t_shell_state *shell_state, char **envp);
static void	clear_shell_state(t_shell_state *shell_state);

void	start_minishell(int argc, char **argv, char **envp)
{
	t_shell_state	shell_state;
	t_list			*cmdlist;
	char			*line;

	(void)argv;
	(void)argc;
	cmdlist = NULL;
	init_shell_state(&shell_state, envp);
	while (1)
	{
		line = readline("🐢shell: ");
		if (!line)
		{
			free(line);
			clear_shell_state(&shell_state);
			clear_history();
			exit(EXIT_SUCCESS);
		}
		if (*line)
		{
			cmdlist = parse_input(line, &shell_state);
			// parse_test(&cmdlist);
			execute_shell(&cmdlist, &shell_state);
			ft_lstclear(&cmdlist, delete_cmd);
			add_history(line);
		}
		free(line);
	}
	clear_shell_state(&shell_state);
}

static void	init_shell_state(t_shell_state *shell_state, char **envp)
{
	size_t	count;

	count = ft_strarray_count(envp);
	shell_state->env.envp = ft_calloc(count + 1, sizeof(char *));
	shell_state->env.envp_name = ft_calloc(count + 1, sizeof(char *));
	shell_state->env.envp_value = ft_calloc(count + 1, sizeof(char *));
	if (!shell_state->env.envp
		|| !shell_state->env.envp_name || !shell_state->env.envp_value)
	{
		free(shell_state->env.envp);
		free(shell_state->env.envp_name);
		free(shell_state->env.envp_value);
		exit(EXIT_FAILURE);
	}
	if (!populate_shell_state(shell_state, envp))
	{
		clear_shell_state(shell_state);
		exit(EXIT_FAILURE);
	}
	shell_state->status = SUCCESS;
}

static int	populate_shell_state(t_shell_state *shell_state, char **envp)
{
	size_t	i;
	size_t	len;
	char	*val;

	i = 0;
	while (envp && envp[i])
	{
		shell_state->env.envp[i] = ft_strdup(envp[i]);
		if (!shell_state->env.envp[i])
			return (0);
		val = ft_strchr(shell_state->env.envp[i], '=');
		len = val - shell_state->env.envp[i];
		shell_state->env.envp_name[i] = ft_substr(envp[i], 0, len);
		if (!shell_state->env.envp_name[i])
			return (0);
		val++;
		shell_state->env.envp_value[i] = ft_strdup(val);
		if (!shell_state->env.envp_value[i])
			return (0);
		i++;
	}
	return (1);
}

static void	clear_shell_state(t_shell_state *shell_state)
{
	ft_free_strarr(shell_state->env.envp);
	ft_free_strarr(shell_state->env.envp_name);
	ft_free_strarr(shell_state->env.envp_value);
}
