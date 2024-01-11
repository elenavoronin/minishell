/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/11 17:20:28 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_all(t_pipes *pipes, t_shell *shell)
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
	if (WIFEXITED(status))
		shell->return_value = WEXITSTATUS(status);
	else
		shell->return_value = 128 + WTERMSIG(status);
}

void	execute_shell(t_list **cmds, t_shell *shell)
{
	int		nr;
	t_pipes	pipes;
	t_cmd	*cmd;

	pipes.nr_pipes = 0;
	nr = ft_lstsize(*cmds) - 1;
	cmd = (*cmds)->content;
	create_pipes_a(cmds, &pipes, shell, nr);
	if (nr == 0 && check_builtins(&cmd->cmd_table[0]) == 1)
	{
		redirect_input(cmds, &pipes, shell);
		redirect_output(cmds, &pipes, shell);
		only_one_builtin(shell);
	}
	else
	{
		get_path_a(*cmds, &pipes, shell);

		create_children(cmds, shell, &pipes);
		wait_all(&pipes, shell);
		clear_pipes(&pipes, nr);
	}
}
