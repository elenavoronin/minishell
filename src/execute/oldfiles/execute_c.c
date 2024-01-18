/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/17 15:42:20 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_pipes(t_pipes *pipes, int nr)
{
	int	i;

	i = 0;
	if (nr > 0)
	{
		while (i < nr)
		{
			free(pipes->path[i]);
			i++;
		}
	}
	free(pipes->pid);
	free(pipes->path);
	free(pipes->fd_arr);
}

void	fork_cmds(t_list *list, int i, t_shell *shell, t_pipes *pipes)
{
	pipes->pid[i] = fork();
	if (pipes->pid[i] < 0)
	{
		perror("fork");
		update_status(shell, FORK_ERROR);
		return ;
	}
	execute_children(list, shell, pipes);
}

void	execute_children(t_list *list, t_shell *shell, t_pipes *pipes)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	while (list)
	{
		cmd = list->content;
		if (pipes->pid[i] != 0)
			return ;
		connect_pipes(i, pipes);
		redirect_input(cmd, pipes, shell, i);
		redirect_output(cmd, pipes, shell, i);
		redirect_stuff(i, pipes);
		if (check_builtins(&cmd->cmd_table[i]) == 1)
		{
			execute_builtins(&cmd->cmd_table[i], shell);
			pipes->return_value = 0;
			return ;
		}
		if (execve(pipes->path[i], &cmd->cmd_table[i], shell->env.envp) == -1)
		{
			perror("execve failed\n");
			pipes->return_value = 127;
			return ;
		}
	}
}

void	create_children(t_list **list, t_shell *shell,
	t_pipes *pipes)
{
	int		i;
	t_cmd	*cmds;

	i = 0;
	while ((*list))
	{
		cmds = (*list)->content;
		fork_cmds(*list, i, shell, pipes);
		i++;
		*list = (*list)->next;
	}
}
