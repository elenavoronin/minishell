/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_a.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 15:32:36 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/15 14:17:24 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int  create_dummy_cmd(t_list **list) //don't forget to delete from here and .h
// {
// 	t_dummy_cmd *dummy_cmd;

// 	// int nr = 2;
// 	int i = 0;
// 	dummy_cmd = malloc(sizeof(t_dummy_cmd));
// 	if (!dummy_cmd)
// 		return (-1);
// 	dummy_cmd->delimiter = 0;
// 	dummy_cmd->infile = 0;
// 	dummy_cmd->outfile = 0;
// 	dummy_cmd->output_flag = 0;
// 	dummy_cmd->status = 0;
// 	char **cmd_table = malloc(sizeof(char *) * 3);
// 	if (!cmd_table)
// 	{
// 		free(dummy_cmd);
// 		return (-1);
// 	}
// 	cmd_table[i] = strdup("echo");
// 	if (!cmd_table[i])
// 	{
// 		free(dummy_cmd);
// 		free(cmd_table);
// 		return (-1);
// 	}
// 	cmd_table[i + 1] = strdup("hello");
// 	if (!cmd_table[i + 1])
// 	{
// 		free(cmd_table[i]);
// 		free(dummy_cmd);
// 		free(cmd_table);
// 		return (-1);
// 	}
// 	cmd_table[i + 2] = NULL;
// 	dummy_cmd->cmd_table = cmd_table;
// 	*list = ft_lstnew(dummy_cmd);
// 	// printf("list %s\n", (char *)((t_dummy_cmd *)(*list)->content)->cmd_table[0]);
// 	return (0);
// }

void	execute_shell(t_list **cmds, t_shell_state *mini_state)
{
	t_pipes_struct	pipes;

	pipes.nr_pipes = 0;
	create_pipes(cmds, &pipes, mini_state);
	create_children(cmds, mini_state, &pipes);
	// proper_exit_code() exit codes should match bash + use the status code for this
}
