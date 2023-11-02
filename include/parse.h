/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 18:00:09 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/02 17:55:15 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

/**
 * Container for parsed input. Create this in stack memory.
 * @param delimiter If not NULL, delimiter for heredoc.
 * @param input If not NULL, name of input file.
 * @param output If not NULL, name of output file.
 * @param output_flag Either 'w' for write, or 'a' for append.
 * @param cmds Commands and args.
 */
typedef struct s_cmd
{
	char	*delimiter;
	char	*input;
	char	*output;
	char	output_flag;
	char	**cmds;
	int		count;
	int		status;
}	t_cmd;

t_list	*parse_input(char *input);
void	parse_free(t_list *head);

#endif