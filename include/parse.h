/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 18:00:09 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/07 18:19:48 by dliu          ########   odam.nl         */
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
	char	*infile;
	char	*outfile;
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

typedef struct s_tokens
{
	size_t	pos;
	size_t	count;
	size_t	rem;
	size_t	delim;
	size_t	infile;
	size_t	outfile;
}	t_tokens;

typedef struct s_parse
{
	t_list	*cmdnode;
	t_cmd	*cmd;
	char	*cmdstr;
	size_t	pos;
	int		status;
}	t_parse;

void	_extract_cmdstr(char *input, t_parse *parse);
void	_extract_cmd(char *input, t_parse *parse);
void	_terminate(t_list **cmdlist, char *message, int status);
void	_delete_cmd(void *content);

#endif