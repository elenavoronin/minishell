/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 15:06:11 by elenavoroni   #+#    #+#                 */
/*   Updated: 2023/12/20 15:37:23 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_minishell(char **envp);
static void	init_shell(t_shell *shell, char **envp);
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

	init_shell(&shell, envp);
	while (shell.status == SUCCESS)
	{
		prompt = get_prompt(&shell);
		shell.line = readline(prompt);
		free(prompt);
		if (!shell.line)
			mini_exit(&shell);
		if (*shell.line)
		{
			parse_input(&shell);
			//parse_test(&shell.cmdlist);
			execute_shell(&shell.cmdlist, &shell);
			add_history(shell.line);
		}
		free(shell.line);
		shell.line = NULL;
		ft_lstclear(&shell.cmdlist, delete_cmd);
		shell.cmdlist = NULL;
	}
	mini_exit(&shell);
}

static void	init_shell(t_shell *shell, char **envp)
{
	shell->status = SUCCESS;
	shell->line = NULL;
	shell->cmdlist = NULL;
	if (!init_env(&shell->env, envp))
		return (update_status(shell, MALLOC_ERROR));
}

static char	*get_prompt(t_shell *shell)
{
	char	*prompt;
	char	*home;
	char	curpath[PATH_MAX];
	size_t	i;

	home = getenvp_value(&shell->env, "HOME");
	getcwd(curpath, PATH_MAX);
	if (ft_strcmp(home, curpath) == 0)
	{
		curpath[0] = '~';
		curpath[1] = '\0';
	}
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
