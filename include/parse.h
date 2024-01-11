/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 18:00:09 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/10 13:16:28 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

/**
 * Container for parsed input.
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

void	parse_input(t_shell *shell);
void	delete_cmd(void *content);

//For parsing internal use.
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
	char	*cmdstr;
	size_t	argc;
	t_cmd	*cmd;
	t_shell	*shell;
}	t_parse;

typedef struct s_split
{
	t_parse		*parse;
	size_t		count;
	int			quote;
	char		*end;
	char		*tag;
	char		**result;
}	t_split;

typedef struct s_expand
{
	char		**strs;
	size_t		count;
}	t_expand;

void	_parse_tokens(t_parse *parse);
char	**_split(t_parse *parse);
char	*_expand(t_split *split);
void	parse_test(t_list **cmdlist);

#endif
