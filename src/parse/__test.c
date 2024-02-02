/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   __test.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 13:06:05 by dliu          #+#    #+#                 */
/*   Updated: 2024/02/02 06:30:04 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

//For testing and debugging use
void	parse_test(t_list *cmdlist)
{
	t_list	*printlist;
	t_cmd	*cmd;
	size_t	i;

	printlist = cmdlist;
	while (printlist)
	{
		cmd = printlist->content;
		if (cmd)
		{
			printf("\ninfile: %s\n", cmd->infile);
			printf("\noutfile: %s\n", cmd->outfile);
			printf("\nout_flag: %c\n", cmd->output_flag);
			printf("\ncmdtable args:");
			i = 0;
			while (cmd->cmd_table && cmd->cmd_table[i])
			{
				printf("	%s\n", cmd->cmd_table[i]);
				i++;
			}
			printf("\n");
		}
		printlist = printlist->next;
	}
}
