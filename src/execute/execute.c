/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/25 13:22:14 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(t_shell *shell, t_pipes *pipes)
{
	int		status;
	int		i;

	i = 0;
	while (i < pipes->nr_pipes)
	{
		if (pipes->pid[i] > 0)
			waitpid(pipes->pid[i], &status, 0);
		i++;
	}
	printf("DONE WAITING\n");
	if (WIFEXITED(status))
		shell->return_value = WEXITSTATUS(status);
	else
		shell->return_value = 128 + WTERMSIG(status);
}

void	execute_children(t_shell *shell, t_pipes *pipes, t_cmd *cmd, int i)
{
	if (!cmd->cmd_table)
		return ;
	if (pipes->nr_pipes)
		close_pipes(pipes, i);
	//reconsider redirecting
	//redirect_input(cmd, pipes, shell, i);
	//redirect_output(cmd, pipes, shell, i);
	if (check_builtins(cmd->cmd_table) == 1)
	{
		execute_builtins(cmd->cmd_table, shell);
		pipes->return_value = 0;
		return ; //exit instead of return
	}
	if (pipes->path[i] == NULL)
	{
		pipes->return_value = 127;
		ft_perror("🐢shell", cmd->cmd_table[0], "command not found.");
		return ; //exit instead of return
	}
	if (execve(pipes->path[i], cmd->cmd_table, shell->env.envp) == -1)
	{
		perror("🐢shell");
		return ; //exit instead of return
	}
}

void	create_children(t_shell *shell, t_pipes *pipes)
{
	int		i;
	t_list	*list;

	i = 0;
	list = shell->cmdlist;
	while ((list))
	{
		pipes->pid[i] = fork();
		if (pipes->pid[i] == 0)
			execute_children(shell, pipes, (t_cmd *)list->content, i);
		i++;
		list = list->next;
	}
	i = 0;
	while (i < pipes->nr_pipes)
	{
		close(pipes->fd_arr[i][0]);
		close(pipes->fd_arr[i][1]);
		i++;
	}
}

void	execute_shell(t_shell *shell)
{
	int		nr;
	t_pipes	pipes;
	t_cmd	*cmd;

	nr = ft_lstsize(shell->cmdlist) - 1;
	cmd = shell->cmdlist->content;
	if (nr == 0 && check_builtins(cmd->cmd_table) == 1)
		execute_builtins(cmd->cmd_table, shell);
	else
	{
		if (create_pipes(&pipes, shell, nr) != SUCCESS)
			return ;
		get_path(shell, &pipes);
		if (shell->status == SUCCESS && !g_sig)
		{
			create_children(shell, &pipes);
			wait_all(shell, &pipes);
		}
		clear_pipes(&pipes, nr);
	}
}
