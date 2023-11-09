/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/09 15:05:29 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list  *create_dummy_cmd(t_list *list) //don't forget to delete from here and .h
{
	t_dummy_cmd *dummy_cmd;

	// int nr = 2;
	int i = 0;
	dummy_cmd = malloc(sizeof(t_dummy_cmd));
	if (!dummy_cmd)
		return (NULL);
	dummy_cmd->delimiter = 0;
	dummy_cmd->infile = 0;
	dummy_cmd->outfile = 0;
	dummy_cmd->output_flag = 0;
	dummy_cmd->status = 0;
	char **cmd_table = malloc(sizeof(char **));
	if (!cmd_table)
		return (NULL);
	cmd_table[i] = "echo";
	cmd_table[i + 1] = "hello";
	dummy_cmd->cmd_table = cmd_table;
	list = ft_lstnew(dummy_cmd);
	if (!list)
		return (NULL);
	return (list);
}

void	execute_shell(t_list *cmds, t_shell_state *mini_state)
{
	t_pipes_struct	pipes;

	pipes.nr_pipes = 0;
	create_pipes(cmds, &pipes, mini_state);
	create_children(cmds, mini_state, &pipes);
	// close the pipe ends that are still open
	// proper_exit_code() exit codes should match bash + use the status code for this
}