/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _extract.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/03 14:40:06 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	_get_token(char *c);

size_t	_extract_cmd(char *input, t_cmd **cmd)
{
 	size_t	pos;
// 	int		token;

 	pos = 0;
 	if (!input || !cmd || !*cmd)
 		return (pos);
// 	if (token == REDIR_IN)
// 		pos = _extract(input, (*cmd)->input);
// 	else if (token == REDIR_HERE)
// 		pos = _extract(input, (*cmd)->delimiter);
// 	else if (token == REDIR_OUT || token == REDIR_APPEND)
// 	{
// 		pos = _extract(input, (*cmd)->output);
// 		if (token == REDIR_APPEND)
// 			(*cmd)->output_flag = 'a';
//	}
	return (pos);
}

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