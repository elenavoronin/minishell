/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:30:16 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/04 12:03:59 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	mini_exit(t_shell *shell)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	free(shell->line);
	ft_lstclear(&shell->cmdlist, delete_cmd);
	clear_env(&shell->env);
	shell->run = 0;
	clear_history();
	exit(shell->return_value);
}
