/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 15:06:11 by elenavoroni   #+#    #+#                 */
/*   Updated: 2024/01/22 18:21:12 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	t_shell				shell;

	(void)argv;
	(void)argc;
	init_signals(&sa);
	shell.return_value = 0;
	shell.line = NULL;
	shell.cmdlist = NULL;
	shell.status = init_env(&shell.env, envp);
	if (shell.status != SUCCESS || g_sig != SUCCESS)
	{
		ft_perror("🐢shell", "init_shell", "Could not initialize envp");
		return (INTERNAL_ERROR);
	}
	start_minishell(&shell);
	return (0);
}
