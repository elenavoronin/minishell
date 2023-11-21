/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _expand.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/21 14:00:31 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_expand_start(t_expand	*expand, t_split *split);
static int	_expand_tag(t_expand *expand, t_split *split);
static int	_expand_end(t_expand *expand, t_split *split);
static char	*expand_join(t_expand	*expand);

char	*_expand(t_split *split)
{
	t_expand	expand;
	char		*result;

	expand.i = 0;
	result = NULL;
	while (split->parse->cmdstr != split->end)
	{
		if (_expand_start(&expand, split))
		{
			if (_expand_tag(&expand, split))
			{
				if (_expand_end(&expand, split))
					result = expand_join(&expand);
			}
		}
	}
	if (!result)
		update_status(split->parse->shell_state, MALLOC_ERROR);
	return (result);
}

static int	_expand_start(t_expand	*expand, t_split *split)
{
	size_t	len;

	if (split->tag == split->parse->cmdstr)
		return (1);
	len = split->tag - split->parse->cmdstr;
	expand->strs[expand->i] = ft_substr(split->parse->cmdstr, 0, len);
	if (!expand->strs[expand->i])
		return (update_status(split->parse->shell_state, MALLOC_ERROR), 0);
	expand->i++;
	return (1);
}

static int	_expand_tag(t_expand *expand, t_split *split)
{
	size_t	len;
	char	*ename;
	char	*evalue;

	split->tag++;
	split->parse->cmdstr = split->tag;
	while (*split->parse->cmdstr && (ft_isalnum(*(split->parse->cmdstr))
			|| *split->parse->cmdstr == '_'))
		split->parse->cmdstr++;
	len = split->parse->cmdstr - split->tag;
	ename = ft_substr(split->tag, 0, len);
	if (!ename)
		return (update_status(split->parse->shell_state, MALLOC_ERROR), 0);
	evalue = getenvp_value(split->parse->shell_state, ename);
	free(ename);
	if (evalue)
	{
		expand->strs[expand->i] = ft_strdup(evalue);
		if (!expand->strs[expand->i])
			return (update_status(split->parse->shell_state, MALLOC_ERROR), 0);
	}
	else
		expand->strs[expand->i] = ft_strdup("");
	expand->i++;
	return (1);
}

static int	_expand_end(t_expand *expand, t_split *split)
{
	size_t	len;

	if (split->parse->cmdstr == split->end)
		return (1);
	len = split->end - split->parse->cmdstr;
	expand->strs[expand->i] = ft_substr(split->parse->cmdstr, 0, len);
	if (!expand->strs[expand->i])
		return (update_status(split->parse->shell_state, MALLOC_ERROR), 0);
	expand->i++;
	split->parse->cmdstr = split->end;
	return (1);
}

static char	*expand_join(t_expand *expand)
{
	int		i;
	char	*tmp;
	char	*joined;

	i = 0;
	joined = NULL;
	while (i < expand->i)
	{
		if (expand->strs[i][0])
		{
			tmp = ft_strjoin(joined, expand->strs[i]);
			if (!tmp)
				return (NULL);
			free(joined);
			free(expand->strs[i]);
			joined = tmp;
		}
		i++;
	}
	if (!joined)
		joined = ft_strdup("");
	return (joined);
}
