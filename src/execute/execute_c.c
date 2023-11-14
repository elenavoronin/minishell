/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_c.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 16:43:51 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/14 08:53:17 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_useless_pipes(int i, t_pipes_struct *pipes)
{
	if (pipes->nr_pipes == i)
		close(pipes->fd_arr[i][0]);
}

int	redirect_stuff(int i, t_pipes_struct *pipes)
{
	int	input;
	int	output;

	input = STDIN_FILENO;
	output = STDOUT_FILENO;
	if (i == 0 && pipes->nr_pipes == 0)
	{
		if (dup2(input, STDIN_FILENO) == -1)
			return (-1);
		if (dup2(output, STDOUT_FILENO) == -1)
			return (-1);
	}
	return (0);
}

void	fork_cmds(char **cmd, int i, t_shell_state *mini_state,
			t_pipes_struct *pipes)
{
	int		j;

	pipes->pid = malloc(sizeof(int *));
	if (!pipes->pid)
		return (update_status_code(mini_state, MALLOC_ERROR));
	pipes->pid[i] = fork();
	if (pipes->pid[i] != 0)
		return ;
	dprintf(1, "I FORK\n");
	close_useless_pipes(i, pipes); 	// close pipe ends i don't need 
	if (redirect_stuff(i, pipes) != 0)
	{
		update_status_code(mini_state, REDIRECT_ERROR);
		return ;
	}
	j = 0;
	while (cmd[j])
		execve(pipes->path, &cmd[j++], (char **)mini_state->mini_env);
	printf("execve failed for some reason\n"); //update to correct error message
	exit(127);
}

void	create_children(t_list **list, t_shell_state *mini_state,
	t_pipes_struct *pipes)
{
	int			i;
	t_dummy_cmd	*cmds;

	i = 1;
	while (list)
	{
		cmds = (*list)->content;
		fork_cmds(cmds->cmd_table, i, mini_state, pipes);
		i++;
		*list = (*list)->next;
	}
}
