/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 15:11:01 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/10 11:24:59 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line = "hello args < infile > outfile << here >> flag";
	t_list	*cmdlist;
	t_list	*printlist;
	t_cmd	*cmd;
	size_t	i;

	printf("\nMinishell Parsing Tester\n");
	if (line)
	{
		if (ft_strncmp(line, "exit", ft_strlen(line)) == 0)
		{
			free(line);
			return (0);
		}
		cmdlist = parse_input(line);
		if (!cmdlist)
		{
			printf("parsing failed!");
			return (0);
		}
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
					printf("	%s", cmd->cmd_table[i]);
					i++;
				}
				printf("\n");
			}
			printlist = printlist->next;
		}
		ft_lstclear(&cmdlist, delete_cmd);
	}
	return (0);
}
