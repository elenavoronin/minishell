/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 18:00:09 by dliu          #+#    #+#                 */
/*   Updated: 2024/02/01 20:51:33 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

typedef enum e_token
{
	ARG,
	IN,
	OUT,
	HERE,
	APPEND,
	PIPE
}	t_token;

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
	char	tmp;
	char	delimiter;
	char	*infile;
	char	*outfile;
	char	output_flag;
	char	**cmd_table;
	size_t	cmd_argc;
}	t_cmd;

int		parse_input(t_shell *shell);

typedef struct s_parse
{
	size_t	i;
	size_t	count;
	char	*cmdstr;
	char	*str;
	char	*pos;
	char	*tmp;
	char	**result;
	t_token	*tokens;
	char	**dest;
	t_cmd	*curcmd;
}	t_parse;

int		_is_symbol(char c);
int		_expand(t_shell *shell, t_parse *parse);
int		_copy_tmp(t_shell *shell, t_parse *parse);
int		_copy_str(t_shell *shell, t_parse *parse, char *str);
int		_copy_fin(t_shell *shell, t_parse *parse);
int		_handle_symbols(t_shell *shell, t_parse *parse);
int		_handle_args(t_shell *shell, t_parse *parse);
int		_tokenise(t_shell *shell, t_parse *parse);
void	parse_test(t_list *cmdlist);
int		parse_check_tokens(char *token);

#endif
