/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/16 15:14:45 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Close unnecessary pipe ends in the child process
void	close_useless_pipes(int i, t_pipes_struct *pipes)
{
	int	j;

	j = 0;
	while (j < pipes->nr_pipes)
	{
		if (j != i)
		{
			close(pipes->fd_arr[j][0]);
			close(pipes->fd_arr[j][1]);
		}
		j++;
	}
}

int	redirect_stuff(int i, t_pipes_struct *pipes)
{
	if (i > 0)
	{
		dup2(pipes->fd_arr[i - 1][0], STDIN_FILENO);
		close(pipes->fd_arr[i - 1][0]);
		close(pipes->fd_arr[i - 1][1]);
	}
	if (i < pipes->nr_pipes - 1)
	{
		dup2(pipes->fd_arr[i][1], STDOUT_FILENO);
		close(pipes->fd_arr[i][0]);
		close(pipes->fd_arr[i][1]);
	}
	return (0);
}

void	clear_pipes(t_pipes_struct *pipes)
{
	int	i;

	i = 0;
	ft_free_strarr(pipes->path);
	while (pipes->fd_arr[i])
	{
		free(pipes->fd_arr[i]);
		free(pipes->pid);
		i++;
	}
	free(pipes->pid);
	free(pipes->fd_arr);
	free(pipes);
}

void	fork_cmds(char **cmd, int i, t_shell_state *mini_state,
			t_pipes_struct *pipes)
{
	pipes->pid = malloc(sizeof(int *) * (pipes->nr_pipes + 1));
	if (!pipes->pid)
		return (update_status_code(mini_state, MALLOC_ERROR));
	pipes->pid[i] = fork();
	if (pipes->pid[i] == -1)
		return (update_status_code(mini_state, FORK_ERROR));
	if (pipes->pid[i] != 0)
		return ;
	close_useless_pipes(i, pipes);
	if (redirect_stuff(i, pipes) != 0)
	{
		update_status_code(mini_state, REDIRECT_ERROR);
		return ;
	}
	execve(*pipes->path, cmd, mini_state->mini_env);
	clear_pipes(pipes);
	clear_mini_env(mini_state);
	// perror("execve");
	fprintf(stderr, "execve failed\n");
	exit(127);
}

void	create_children(t_list **list, t_shell_state *mini_state,
	t_pipes_struct *pipes)
{
	int			i;
	t_dummy_cmd	*cmds;

	i = 1;
	while (*list)
	{
		cmds = (*list)->content;
		fork_cmds(cmds->cmd_table, i, mini_state, pipes);
		i++;
		*list = (*list)->next;
	}
}
