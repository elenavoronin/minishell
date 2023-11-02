/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 14:29:07 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/02 18:05:48 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "minishell.h"

typedef struct s_tokens
{
	size_t			size;
	char			*cmd;
	char			**args;
	struct s_tokens	*next;
}	t_tokens;

enum e_state
{
	WORD,
	REDIR_IN,
	REDIR_HERE,
	REDIR_OUT,
	REDIR_APPEND
};

// int		_extract_token(t_cmd *cmdnode, char *input, int token);
// size_t	*_extract(char *input, char *buffer);

#endif