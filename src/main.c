/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 15:06:11 by elenavoroni   #+#    #+#                 */
/*   Updated: 2024/01/12 18:20:58 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_minishell(char **envp);
static int	init_shell(t_shell *shell, char **envp);
static char	*get_prompt(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;

	(void)argv;
	(void)argc;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = &signal_handler;
	sigaction(SIGINT, &sa, NULL);
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
		if (!shell.line)
			break ;
		add_history(shell.line);
		parse_input(&shell);
		if (DEBUG)
			parse_test(&shell.cmdlist);
		if (shell.status == SUCCESS)
			execute_shell(&shell.cmdlist, &shell);
		shell.run = init_shell(&shell, NULL);
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
	if (envp)
	{
		if (!init_env(&shell->env, envp))
		{
			ft_perror("🐢shell", "init_shell", "Could not initialize envp");
			shell->return_value = INTERNAL_ERROR;
			return (0);
		}
	}
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

int	update_status(t_shell *shell, t_status code)
{
	shell->status = code;
	return (code);
}
