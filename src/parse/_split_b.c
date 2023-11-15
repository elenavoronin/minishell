/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split_b.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/15 13:01:50 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	_extract_quote_literal(char *line, t_split *split)
{
	size_t	len;

	len = 0;
	if (ft_isquote(*line) == 1)
	{
		line++;
		split->pos = ft_strchr(line, '\'');
		len = split->pos - line;
		split->result[split->count] = ft_substr(line, 0, len);
		if (!split->result[split->count])
			*(split->status) = MALLOC_ERROR;
		split->count++;
		len += 2;
	}
	return (len);
}

size_t	_extract_quote_expand(char *line, t_split *split)
{
	size_t	len;

	len = 0;
	if (ft_isquote(*line) == 2)
	{
		line++;
		split->pos = ft_strchr(line, '\"');
		len = split->pos - line;
		split->result[split->count] = ft_substr(line, 0, len);
		if (!split->result[split->count])
			*(split->status) = MALLOC_ERROR;
		split->count++;
		len += 2;
	}
	return (len);
}

size_t	_extract_word(char *line, t_split *split)
{
	char	*pos;
	size_t	len;

	len = 0;
	if (*line && !ft_isspace(*line) && !ft_isquote(*line))
	{
		pos = line;
		while (pos && *pos && !ft_isspace(*pos) && !ft_isquote(*pos))
			pos++;
		len = pos - line;
		split->result[split->count] = ft_substr(line, 0, len);
		if (!split->result[split->count])
			*(split->status) = MALLOC_ERROR;
		split->count++;
	}
	return (len);
}
