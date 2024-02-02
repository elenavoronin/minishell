/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 15:06:11 by elenavoroni   #+#    #+#                 */
/*   Updated: 2024/02/02 06:50:54 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_shell(t_shell *shell);
static char	*get_prompt(t_shell *shell);

int	g_sig = SUCCESS;

void	start_minishell(t_shell	*shell)
{
	char	*prompt;

	while (1)
	{
		prompt = get_prompt(shell);
		g_sig = READLINE;
		shell->line = readline(prompt);
		g_sig = SUCCESS;
		free(prompt);
		add_history(shell->line);
		if (!shell->line)
			mini_exit(shell, NULL, STDOUT_FILENO);
		if (g_sig == SUCCESS)
			shell->return_value = parse_input(shell);
		if (DEBUG)
			parse_test(shell->cmdlist);
		if (shell->cmdlist && shell->status == SUCCESS && g_sig == SUCCESS)
			execute_shell(shell);
		clear_shell(shell);
	}
	write(STDERR_FILENO, "\nWTF\n", 5);
	mini_exit(shell, NULL, STDOUT_FILENO);
}

static char	*get_prompt(t_shell *shell)
{
	char	*prompt;
	char	*home;
	char	curpath[PATH_MAX];
	size_t	i;

	ft_bzero(&curpath, PATH_MAX);
	home = getenv_value(shell->env, "HOME");
	getcwd(curpath, PATH_MAX);
	if (ft_strcmp(home, curpath) == 0)
		prompt = ft_strjoin("🐢shell:~", "$ ");
	else if (home)
	{
		i = 0;
		while (curpath[i] == home[i])
			i++;
		if (i == ft_strlen(home))
			prompt = ft_joinstrs(3, "🐢shell:~", &curpath[i], "$ ");
		else
			prompt = ft_joinstrs(3, "🐢shell:", curpath, "$ ");
	}
	else
		prompt = ft_joinstrs(3, "🐢shell:", curpath, "$ ");
	if (!prompt)
		update_status(shell, MALLOC_ERROR);
	return (prompt);
}

static void	clear_shell(t_shell *shell)
{
	free(shell->line);
	shell->line = NULL;
	ft_lstclear(&shell->cmdlist, delete_cmd);
	shell->cmdlist = NULL;
	update_status(shell, SUCCESS);
}

void	delete_cmd(void *content)
{
	t_cmd	*cmd;

	if (content)
	{
		cmd = content;
		ft_free_strarr(cmd->cmd_table);
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
	}
}

int	update_status(t_shell *shell, t_status code)
{
	shell->status = code;
	return (code);
}
