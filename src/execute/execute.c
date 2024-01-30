/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/30 16:03:53 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(t_shell *shell, t_pipes *pipes)
{
	int		status;
	int		i;

	i = 0;
	while (i <= pipes->nr_pipes)
	{
		if (pipes->pid[i] > 0)
			waitpid(pipes->pid[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		shell->return_value = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		shell->return_value = 128 + WTERMSIG(status);
}

void	execute_children(t_shell *shell, t_pipes *pipes, t_cmd *cmd, int i)
{
	shell->return_value = 0;
	close_pipes(pipes, i);
	redirect_input(cmd, pipes, shell, i);
	redirect_output(cmd, pipes, shell, i);
	if (shell->return_value != 0)
	{
		perror("🐢shell");
		exit(shell->return_value);
	}
	if (!cmd->cmd_table)
		exit(shell->return_value);
	if (check_builtins(cmd->cmd_table) == 1)
	{
		execute_builtins(cmd->cmd_table, pipes, shell, i);
		exit(shell->return_value);
	}
	if (pipes->path[i] == NULL)
	{
		shell->return_value = 127;
		ft_perror("🐢shell", cmd->cmd_table[0], "command not found.");
		exit(shell->return_value);
	}
	if (execve(pipes->path[i], cmd->cmd_table, shell->env.envp) == -1)
	{
		perror("🐢shell");
		exit(shell->return_value);
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
	if (pipes->nr_pipes != 0)
	{
		while (i < pipes->nr_pipes)
		{
			close(pipes->fd_arr[i][0]);
			close(pipes->fd_arr[i][1]);
			i++;
		}
	}
}

void	execute_shell(t_shell *shell)
{
	int		nr;
	t_pipes	pipes;
	t_cmd	*cmd;

	nr = ft_lstsize(shell->cmdlist) - 1;
	cmd = shell->cmdlist->content;
	if (create_pipes(&pipes, shell, nr) != SUCCESS)
		return ;
	if (nr == 0 && check_builtins(cmd->cmd_table) == 1)
	{
		redirect_sgl_builtin(cmd, &pipes, shell);
		execute_builtins(cmd->cmd_table, &pipes, shell, 0);
		clear_pipes(&pipes, nr);
	}
	else
	{
		get_path(shell, &pipes);
		if (shell->status == SUCCESS && !g_sig)
		{
			create_children(shell, &pipes);
			wait_all(shell, &pipes);
		}
		clear_pipes(&pipes, nr);
	}
}
