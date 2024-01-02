/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 15:06:11 by elenavoroni   #+#    #+#                 */
/*   Updated: 2024/01/02 15:41:50 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_minishell(char **envp);
static int	init_shell(t_shell *shell, char **envp);
static char	*get_prompt(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa_c;
	struct sigaction	sa_q;

	(void)argv;
	(void)argc;
	sa_c.sa_handler = &signal_handler;
	sa_q.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa_c, NULL) != 0 || sigaction(SIGQUIT, &sa_q, NULL) != 0)
	{
		perror("🐢shell");
		return (0);
	}
	start_minishell(envp);
	return (0);
}

static void	start_minishell(char **envp)
{
	t_shell	shell;
	char	*prompt;

	shell.run = init_shell(&shell, envp);
	while (shell.run)
	{
		prompt = get_prompt(&shell);
		shell.line = readline(prompt);
		free(prompt);
		if (!shell.line || ft_strcmp(shell.line, "exit") == 0)
			mini_exit(&shell);
		parse_input(&shell);
		//parse_test(&shell.cmdlist);
		if (shell.status == SUCCESS)
			execute_shell(&shell.cmdlist, &shell);
		add_history(shell.line);
		init_shell(&shell, NULL);
	}
	mini_exit(&shell);
}

static int	init_shell(t_shell *shell, char **envp)
{
	if (!envp)
	{
		free(shell->line);
		ft_lstclear(&shell->cmdlist, delete_cmd);
	}
	shell->line = NULL;
	shell->cmdlist = NULL;
	if (envp && !init_env(&shell->env, envp))
		return (update_status(shell, MALLOC_ERROR), 0);
	return (update_status(shell, SUCCESS), 1);
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
