/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/14 12:17:31 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_useless_pipes(int cmd_index, t_pipes_struct *pipes)
{
	int	index_in;
	int	index_out;
	int	i;

	index_in = cmd_index - 0;
	index_out = cmd_index;
	i = 1;
	while (i <= pipes->nr_pipes)
	{
		if (i != index_in)
			close(pipes->fd_arr[i][0]);
		if (i != index_out)
			close(pipes->fd_arr[i][1]);
		i += 1;
	}
}

int	redirect_stuff(int cmd_index, t_pipes_struct *pipes)
{
	if (dup2(pipes->fd_arr[cmd_index - 1][0], STDIN_FILENO) == -1)
		return (-1);
	if (dup2(pipes->fd_arr[cmd_index][1], STDOUT_FILENO) == -1)
		return (-1);
	return (0);
}

void	fork_cmds(char **cmd, int i, t_shell_state *mini_state,
			t_pipes_struct *pipes)
{
	pipes->pid = malloc(sizeof(int *));
	if (!pipes->pid)
		return (update_status_code(mini_state, MALLOC_ERROR));
	pipes->pid[i] = fork();
	if (pipes->pid[i] != 0)
		return ;
	close_useless_pipes(i, pipes);
	if (redirect_stuff(i, pipes) != 0)
	{
		update_status_code(mini_state, REDIRECT_ERROR);
		return ;
	}
	execve(pipes->path, cmd, mini_state->mini_env);
	printf("execve failed\n"); //update to correct error message
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
