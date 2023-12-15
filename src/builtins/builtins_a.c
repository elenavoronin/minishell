/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_a.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 13:23:27 by elenavoroni   #+#    #+#                 */
/*   Updated: 2023/12/15 11:28:56 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_builtins(char **cmd)
{
	if (ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "exit") == 0
		|| ft_strcmp(cmd[0], "unset") == 0
		|| ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "echo") == 0
		|| ft_strcmp(cmd[0], "cd") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	return (0);
}

void	execute_builtins(char **cmd, t_shell *shell)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		mini_env(shell->env);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		mini_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		mini_pwd(shell);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		mini_cd(cmd, shell);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		mini_exit(shell);
}
