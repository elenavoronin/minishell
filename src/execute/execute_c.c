/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/12 13:07:45 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_pipes(int i, t_pipes *pipes)
{
	if (i > 0)
		pipes->fd_arr[i][0] = pipes->fd_arr[i - 1][1];
}

int	redirect_stuff(int i, t_pipes *pipes)
{
	if (i > 0)
	{
		if (pipes->fd_arr[i][0] != STDIN_FILENO)
		{
			if (dup2(pipes->fd_arr[i][0], STDIN_FILENO) == -1)
				return (perror("dup2"), -1);
			close(pipes->fd_arr[i][0]);
		}
	}
	if (i < pipes->nr_pipes)
	{
		if (pipes->fd_arr[i][1] != STDOUT_FILENO)
		{
			if (dup2(pipes->fd_arr[i][1], STDOUT_FILENO) == -1)
				return (perror("dup2"), -1);
			close(pipes->fd_arr[i][1]);
		}
	}
	return (0);
}

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

void	fork_cmds(char **cmd, int i, t_shell *shell, t_pipes *pipes)
{
	pipes->pid[i] = fork();
	if (pipes->pid[i] < 0)
	{
		perror("fork");
		update_status(shell, FORK_ERROR);
		return ;
	}
}

void	init_children(t_list *list, t_shell *shell, t_pipes *pipes)
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
		redirect_input(list, pipes, shell, i);
		redirect_output(list, pipes, shell, i);
		redirect_stuff(i, pipes);
		if (check_builtins(cmd) == 1)
		{
			execute_builtins(cmd, shell);
			pipes->return_value = 0;
			return ;
		}
		if (execve(pipes->path[i], cmd, shell->env.envp) == -1)
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
		fork_cmds(cmds->cmd_table, i, shell, pipes);
		i++;
		*list = (*list)->next;
	}
	init_children(list, shell, pipes);
}
