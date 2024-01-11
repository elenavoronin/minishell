/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 13:23:27 by elenavoroni   #+#    #+#                 */
/*   Updated: 2024/01/11 16:20:11 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	only_one_builtin(t_shell *shell)
{
	t_cmd	*cmd;

	if (ft_lstsize(shell->cmdlist) == 1)
	{
		cmd = shell->cmdlist->content;
		if (check_builtins(cmd->cmd_table))
		{
			execute_builtins(cmd->cmd_table, shell);
			return (1);
		}
	}
	return (0);
}

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
	else if (ft_strcmp(cmd[0], "unset") == 0)
		mini_unset(cmd, shell);
	else if (ft_strcmp(cmd[0], "export") == 0)
		mini_export(cmd, shell);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		mini_exit(shell);
}
