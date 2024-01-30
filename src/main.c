/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/03 15:06:11 by elenavoroni   #+#    #+#                 */
/*   Updated: 2024/01/30 16:00:50 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell				shell;

	(void)argv;
	(void)argc;
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
