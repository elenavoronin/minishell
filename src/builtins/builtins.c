/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 13:23:27 by elenavoroni   #+#    #+#                 */
/*   Updated: 2024/01/31 12:48:11 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_builtins(char **cmd)
{
	if (cmd == NULL)
		return (2);
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

void	execute_builtins(char **cmd, t_pipes *pipes, t_shell *shell, int i)
{
	if (!cmd)
		return ;
	if (ft_strcmp(cmd[0], "env") == 0)
		shell->return_value = mini_env(shell->env, pipes->outfile[i]);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		shell->return_value = mini_echo(cmd, pipes->outfile[i]);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		shell->return_value = mini_pwd(shell, pipes->outfile[i]);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		shell->return_value = mini_cd(cmd, shell);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		shell->return_value = mini_unset(cmd, shell);
	else if (ft_strcmp(cmd[0], "export") == 0)
		shell->return_value = mini_export(cmd, shell, pipes->outfile[i]);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		shell->return_value = mini_exit(shell, cmd, pipes->outfile[i]);
}
