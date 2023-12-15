/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 15:06:11 by elenavoroni   #+#    #+#                 */
/*   Updated: 2023/12/15 14:34:23 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_minishell(char **envp);
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
	t_list	*cmdlist;
	char	*line;
	char	*prompt;

	cmdlist = NULL;
	init_env(&shell, envp);
	while (shell.status == SUCCESS)
	{
		prompt = get_prompt(&shell);
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			free(line);
			clear_env(&shell);
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
	clear_env(&shell);
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
