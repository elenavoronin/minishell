/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split_b.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/16 13:55:10 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_extract_quote_literal(t_split *split)
{
	size_t	len;

	split->line++;
	split->pos = ft_strchr(split->line, '\'');
	len = split->pos - split->line;
	split->result[split->count] = ft_substr(split->line, 0, len);
	if (!split->result[split->count])
		*(split->status) = MALLOC_ERROR;
	split->count++;
	split->line = split->pos;
	split->line++;
}

char	*_expand_tag(t_split *split)
{
	size_t	len;
	char	*expand;

	split->pos = split->tag + 1;
	while (ft_isalnum(*split->pos) || split->pos == '_')
		split->pos++;
	len = split->pos - split->tag + 1;
	expand = ft_substr(split->tag, 0, len);
	if (!expand)
		*(split->status) = MALLOC_ERROR;
	return (expand);
}

void	_extract_quote_expand(t_split *split)
{
	size_t	len;
	char	*tag;
	char	*expand;
	char	*end;
	char	*tmp;
	
	split->line++;
	split->pos = ft_strchr(split->line, '\"');
	split->tag = ft_strchr(split->line, '$');
	if (split->tag < split->pos)
	{
		expand = _expand_tag(split);
		end = split->pos;
		while (*end)
			end++;
		len = end - split->pos;
		tmp = ft_substr(split->pos, 0, len);
	}
	//
	split->pos = ft_strchr(split->line, '\"');
	len = split->pos - split->line;
	split->result[split->count] = ft_substr(split->line, 0, len);
	if (!split->result[split->count])
		*(split->status) = MALLOC_ERROR;
	split->count++;
	len += 2;
}

void	_extract_word(t_split *split)
{
	size_t	len;

	split->pos = split->line;
	while (*split->pos && !ft_isspace(*split->pos) && !ft_isquote(*split->pos))
		split->pos++;
	len = split->pos - split->line;
	split->result[split->count] = ft_substr(split->line, 0, len);
	if (!split->result[split->count])
		*(split->status) = MALLOC_ERROR;
	split->count++;
}
