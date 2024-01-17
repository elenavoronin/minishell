/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   __test.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 13:06:05 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/16 13:27:18 by dliu          ########   odam.nl         */
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
			printf("\ndelimiter: %s\n", cmd->delimiter);
			printf("\ninfile: %s\n", cmd->infile);
			printf("\noutfile: %s\n", cmd->outfile);
			printf("\nout_flag: %c\n", cmd->output_flag);
			i = 0;
			printf("\ncmdtable args:");
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
