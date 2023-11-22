/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _extract.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/22 18:54:23 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_extract_expand(t_split *split);

void	_extract(t_split *split)
{
	split->quote = ft_isquote(*(split->parse->cmdstr));
	split->tag = ft_strchr(split->parse->cmdstr, '$');
	if (split->quote)
	{
		split->end = ft_strchr(split->parse->cmdstr + 1, *split->parse->cmdstr);
		split->parse->cmdstr++;
		_extract_expand(split);
		split->parse->cmdstr++;
		split->quote = 0;
	}
	else
	{
		split->end = split->parse->cmdstr;
		while (*split->end
			&& !ft_isspace(*split->end) && !ft_isquote(*split->end))
			split->end++;
		_extract_expand(split);
	}
}

static void	_extract_expand(t_split *split)
{
	size_t	len;

	if (split->tag && split->tag < split->end && split->quote != 1)
		split->result[split->count] = _expand(split);
	else
	{
		len = split->end - split->parse->cmdstr;
		split->result[split->count] = ft_substr(split->parse->cmdstr, 0, len);
		split->parse->cmdstr = split->end;
	}
	if (!split->result[split->count])
		return (update_status(split->parse->shell_state, MALLOC_ERROR));
	split->count++;
}
