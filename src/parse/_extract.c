/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _extract.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/20 20:11:25 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_extract_quote(t_split *split);
static void	_extract_expand(t_split *split, int expand);

void	_extract(t_split *split)
{
	split->quote = ft_isquote(*(split->parse->cmdstr));
	if (split->quote)
	{
		split->end = ft_strchr(split->parse->cmdstr + 1, *split->parse->cmdstr);
		_extract_quote(split);
	}
	else
	{
		split->end = split->parse->cmdstr;
		while (*split->end
			&& !ft_isspace(*split->end) && !ft_isquote(*split->end))
			split->end++;
		_extract_expand(split, 1);
	}
}

static void	_extract_quote(t_split *split)
{
	split->parse->cmdstr++;
	if (split->end == split->parse->cmdstr)
	{
		_extract_expand(split, 0);
		split->parse->cmdstr++;
		return ;
	}
	if (split->quote == 2)
	{
		split->tag = ft_strchr(split->parse->cmdstr, '$');
		if (split->tag && split->tag < split->end)
		{
			_extract_expand(split, 1);
			split->parse->cmdstr++;
			return ;
		}
	}
	_extract_expand(split, 0);
	split->parse->cmdstr++;
}

static void	_extract_expand(t_split *split, int expand)
{
	size_t	len;

	if (!expand)
	{
		len = split->end - split->parse->cmdstr;
		split->result[split->count] = ft_substr(split->parse->cmdstr, 0, len);
	}
	else if (expand && split->tag == split->parse->cmdstr)
		split->result[split->count] = _expand(split);
	else if (expand && split->quote == 2)
		split->result[split->count] = _expand(split);
	if (!split->result[split->count])
		return (update_status(split->parse->shell_state, MALLOC_ERROR));
	split->count++;
	split->parse->cmdstr = split->end;
}
