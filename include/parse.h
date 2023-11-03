/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 18:00:09 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/03 14:25:02 by dliu          ########   odam.nl         */
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
	char	**cmd_table;
	int		status;
}	t_cmd;

t_list	*parse_input(char *input);
void	parse_free(t_list **cmdlist);

//For parsing internal use, WARNING: VOLATILE
enum e_state
{
	WORD,
	REDIR_IN,
	REDIR_HERE,
	REDIR_OUT,
	REDIR_APPEND
};

size_t	_extract_cmd(char *input, t_cmd **cmd);
void	_terminate_parsing(t_list **cmdlist, char *message);
void	_delete_cmd(void *content);

#endif