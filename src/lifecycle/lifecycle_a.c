/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_a.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:58:48 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/14 11:29:55 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell_state(t_shell *shell, char **envp);
static int	populate_shell_state(t_shell *shell, char **envp);
static char	*get_prompt(t_shell *shell);
static void	clear_shell_state(t_shell *shell);

void	start_minishell(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_list	*cmdlist;
	char	*line;
	char	*prompt;

	(void)argv;
	(void)argc;
	cmdlist = NULL;
	init_shell_state(&shell, envp);
	while (1)
	{
		prompt = get_prompt(&shell);
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			free(line);
			clear_shell_state(&shell);
			clear_history();
			exit(EXIT_SUCCESS);
		}
		if (*line)
		{
			cmdlist = parse_input(line, &shell);
			// parse_test(&cmdlist);
			execute_shell(&cmdlist, &shell);
			ft_lstclear(&cmdlist, delete_cmd);
			add_history(line);
		}
		free(line);
	}
	clear_shell_state(&shell);
}

static void	init_shell_state(t_shell *shell, char **envp)
{
	size_t	count;

	count = ft_strarray_count(envp);
	shell->env.envp = ft_calloc(count + 1, sizeof(char *));
	shell->env.envp_name = ft_calloc(count + 1, sizeof(char *));
	shell->env.envp_value = ft_calloc(count + 1, sizeof(char *));
	if (!shell->env.envp || !shell->env.envp_name || !shell->env.envp_value)
	{
		clear_shell_state(shell);
		exit(EXIT_FAILURE);
	}
	if (!populate_shell_state(shell, envp))
	{
		clear_shell_state(shell);
		exit(EXIT_FAILURE);
	}
	shell->status = SUCCESS;
}

static int	populate_shell_state(t_shell *shell, char **envp)
{
	size_t	i;
	size_t	len;
	char	*val;

	i = 0;
	while (envp && envp[i])
	{
		shell->env.envp[i] = ft_strdup(envp[i]);
		val = ft_strchr(envp[i], '=');
		len = val - envp[i];
		shell->env.envp_name[i] = ft_substr(envp[i], 0, len);
		if (!shell->env.envp_name[i])
			return (0);
		val++;
		shell->env.envp_value[i] = ft_strdup(val);
		if (!shell->env.envp_value[i])
			return (0);
		i++;
	}
	return (1);
}

static char	*get_prompt(t_shell *shell)
{
	char	*curpath;
	char	*prompt;
	char	*home;
	size_t	i;

	home = getenvp_value(shell, "HOME");
	curpath = getenvp_value(shell, "PWD");
	if (ft_strcmp(home, curpath) == 0)
		curpath = "~";
	i = 0;
	while (curpath[i] == home[i])
		i++;
	if (i == ft_strlen(home))
		prompt = ft_joinstrs(3, "🐢shell:~", &curpath[i], "$ ");
	else
		prompt = ft_joinstrs(3, "🐢shell:", curpath, "$ ");
	return (prompt);
}

static void	clear_shell_state(t_shell *shell)
{
	ft_free_strarr(shell->env.envp);
	ft_free_strarr(shell->env.envp_name);
	ft_free_strarr(shell->env.envp_value);
}
