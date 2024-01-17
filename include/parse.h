/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 18:00:09 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/16 20:55:43 by dliu          ########   odam.nl         */
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
	char	*delimiter;
	char	*infile;
	char	*outfile;
	char	output_flag;
	char	**cmd_table;
	size_t	cmd_argc;
}	t_cmd;

int		parse_input(t_shell *shell);

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
	char	*line;
	char	*pos;
	char	*cmdstr;
}	t_parse;

typedef struct s_split
{
	char	*str;
	char	*pos;
	char	*tmp;
	char	**result;
}	t_split;

int		_expand(t_parse *parse, t_shell *shell);
char	**_split(char *s);
int		_tokenise(char	**tokens, t_shell *shell);
void	parse_test(t_list *cmdlist);

#endif
