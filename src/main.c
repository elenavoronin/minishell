/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 15:06:11 by elenavoroni   #+#    #+#                 */
/*   Updated: 2023/12/17 17:05:23 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_minishell(char **envp);
static void	init(t_shell *shell, char **envp);
static char	*get_prompt(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	start_minishell(envp);
	return (0);
}

static void	start_minishell(char **envp)
{
	t_shell	shell;
	char	*prompt;
	char	*line;

	init(&shell, envp);
	while (shell.status == SUCCESS)
	{
		prompt = get_prompt(&shell);
		line = readline(prompt);
		free(prompt);
		if (!line)
			mini_exit(&shell);
		if (*line)
		{
			shell.line = line;
			parse_input(&shell);
			//parse_test(&shell.cmdlist);
			execute_shell(&shell.cmdlist, &shell);
			add_history(line);
		}
		free(line);
		line = NULL;
	}
	clear_history();
	clear_env(&shell);
}

static void	init(t_shell *shell, char **envp)
{
	shell->status = SUCCESS;
	shell->line = NULL;
	shell->cmdlist = NULL;
	init_env(shell, envp);
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
	if (!prompt)
		update_status(shell, MALLOC_ERROR);
	return (prompt);
}

void	update_status(t_shell *shell, t_status code)
{
	shell->status = code;
}
