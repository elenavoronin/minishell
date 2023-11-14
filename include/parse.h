/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 18:00:09 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/14 16:53:01 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

/**
 * Container for parsed input. Create this in stack memory.
 * @param delimiter If not NULL, delimiter for heredoc.
 * @param infile If not NULL, name of input file.
 * @param outfile If not NULL, name of output file.
 * @param output_flag Either 'w' for write, or 'a' for append.
 * @param cmd_table Command with args.
 */
typedef struct s_cmd
{
	char				*delimiter;
	char				*infile;
	char				*outfile;
	char				output_flag;
	char				**cmd_table;
}	t_cmd;

t_list	*parse_input(char *input);
void	delete_cmd(void *content);

//For parsing internal use, WARNING: VOLATILE
typedef enum e_token_type
{
	EMPTY,
	WORD,
	REDIR_IN,
	REDIR_HERE,
	REDIR_OUT,
	REDIR_APPEND
}	t_token_type;

typedef struct s_parse
{
	char			*cmdstr;
	char			**tokens;
	t_cmd			*cmd;
	size_t			pos;
	size_t			argc;
	t_code_status	status;
}	t_parse;

typedef enum e_quote
{
	NO_Q,
	SINGLE_Q,
	DOUBLE_Q
}	t_quote;

typedef struct s_split
{
	size_t			count;
	t_quote			quoted;
	char			*pos;
	char			**result;
	t_code_status	*status;
}	t_split;

void	_extract_cmdstr(char *input, t_parse *parse);
void	_tokens_to_cmd(t_parse *parse);
char	**_split_and_expand(char *line, t_code_status *status);
void	_terminate(t_list **cmdlist, char *message, int status);

void	parse_test(t_list **cmdlist);

#endif