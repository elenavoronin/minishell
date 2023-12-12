/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/11 11:43:32 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	connect_pipes(int i, t_pipes_struct *pipes)
{
	if (i > 0)
		pipes->fd_arr[i][0] = pipes->fd_arr[i - 1][1];
}

int	redirect_stuff(int i, t_pipes_struct *pipes)
{
	if (i > 0)
	{
		if (dup2(pipes->fd_arr[i - 1][0], STDIN_FILENO) == -1)
			return (-1);
		close(pipes->fd_arr[i - 1][0]);
		close(pipes->fd_arr[i - 1][1]);
	}
	if (i < pipes->nr_pipes)
	{
		if (dup2(pipes->fd_arr[i][1], STDOUT_FILENO) == -1)
			return (-1);
		close(pipes->fd_arr[i][0]);
		close(pipes->fd_arr[i][1]);
	}
	return (0);
}

void	clear_pipes(t_pipes_struct *pipes, int nr)
{
	int	i;

	i = 0;
	if (nr > 0)
	{
		while (pipes->fd_arr[i])
		{
			free(pipes->fd_arr[i]);
			free(pipes->pid);
			i++;
		}
	}
	free(pipes->pid);
	free(pipes->path);
	free(pipes->fd_arr);
}

void	fork_cmds(char **cmd, int i, t_shell_state *shell_state,
			t_pipes_struct *pipes)
{
	pipes->pid[i] = fork();
	if (pipes->pid[i] < 0)
	{
		perror("fork");
		return (update_status(shell_state, FORK_ERROR));
	}
	if (pipes->pid[i] != 0)
		return ;
	connect_pipes(i, pipes);
	if (redirect_stuff(i, pipes) != 0)
	{
		update_status(shell_state, REDIRECT_ERROR);
		return ;
	}
	if (check_builtins(cmd) == 1)
	{
		execute_builtins(cmd, shell_state);
		return ;
	}
	if (execve(pipes->path, cmd, shell_state->env.envp) == -1)
	{
		clear_pipes(pipes, pipes->nr_pipes);
		fprintf(stderr, "execve failed\n");
		exit(127);
	}
}

void	create_children(t_list **list, t_shell_state *shell_state,
	t_pipes_struct *pipes)
{
	int		i;
	t_cmd	*cmds;

	i = 0;
	while (*list)
	{
		cmds = (*list)->content;
		fork_cmds(cmds->cmd_table, i, shell_state, pipes);
		i++;
		*list = (*list)->next;
	}
}
