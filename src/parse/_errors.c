/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _errors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 13:06:05 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/14 14:12:29 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Encountered parsing error, terminates program with given exit code.
void	_terminate(t_list **cmdlist, t_parse *parse, char *message, int status)
{
	_free_parse(parse);
	ft_lstclear(cmdlist, delete_cmd);
	ft_errexit(message, status);
}

//For testing and debugging use
void	parse_test(t_list **cmdlist)
{
	t_list	*printlist;
	t_cmd	*cmd;
	size_t	i;

	printlist = *cmdlist;
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
}

/*
int	main(void)
{
	t_list		*cmdlist;
	static char	line[128] = "hello 'args' < infile > outfile << here \
		 >> outfile_append 'args again'";

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
		parse_test(&cmdlist);
		ft_lstclear(&cmdlist, delete_cmd);
	}
	return (0);
}
*/
