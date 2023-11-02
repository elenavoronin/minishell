/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _token.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/02 18:05:20 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

// int	_get_token(char *c)
// {
// 	if (*c == '<')
// 	{
// 		if (c + 1 == '<')
// 			return (REDIR_HERE);
// 		return (REDIR_IN);
// 	}
// 	if (c == '>')
// 	{
// 		if (c + 1 == '>')
// 			return (REDIR_APPEND);
// 		return (REDIR_OUT);
// 	}
// 	return (WORD);
// }

// int	_extract_token(t_cmd *cmdnode, char *input, int token)
// {
// 	size_t	pos;

// 	pos = 0;
// 	if (token == REDIR_IN)
// 		pos = _extract(input, cmdnode->input);
// 	else if (token == REDIR_HERE)
// 		pos = _extract(input, cmdnode->delimiter);
// 	else if (token == REDIR_OUT || token == REDIR_APPEND)
// 	{
// 		pos = _extract(input, cmdnode->output);
// 		if (token == REDIR_APPEND)
// 			cmdnode->output_flag = 'a';
// 	}
// 	else
// 		pos = _extract_cmd(input, cmdnode);
// 	return (pos);
// }

// //consider replacing with split2
// size_t	*_extract(char *input, char *buffer)
// {
// 	int	count;
// 	int	quote_double;
// 	int	quote_single;

// 	count = 0;
// 	quote_double = 0;
// 	quote_single = 0;
// 	while (*(input + count))
// 	{
// 		if (*input == '\'')
// 			quote_single = quote_single ^ 1;
// 		else if (*input == '\"')
// 			quote_double = quote_double ^ 1;
// 		if (!quote_double && !quote_single && ft_isspace(*input))
// 			count++;
// 		else
// 		{
// 			if (!quote_single && *input == '$')
// 				count += _extract_expanded(input, buffer);
// 			count++;
// 		}
// 	}
// 	if (quote_single || quote_double)
// 	{
// 		ft_perror("Turtleshell", "extract()", "Unclosed quotation marks.");
// 		return (-1);
// 	}
// 	return (count);
// }
