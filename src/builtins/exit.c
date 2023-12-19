/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:30:16 by dliu          #+#    #+#                 */
/*   Updated: 2023/12/18 10:48:28 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//needs to exit before forking if this is the only command
void	mini_exit(t_shell *shell)
{
	clear_history();
	free(shell->line);
	ft_lstclear(&shell->cmdlist, delete_cmd);
	clear_env(&shell->env);
	exit(shell->status);
}
