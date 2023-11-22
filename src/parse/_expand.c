/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _expand.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/22 19:46:20 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			_init_expand(t_expand *expand, t_split *split);
static void	_extract_tag(t_expand *expand, t_split *split);
static void	_extract_word(t_expand *expand, t_split *split);
static char	*_join_strs(t_expand *expand);

char	*_expand(t_split *split)
{
	t_expand	expand;
	char		*expanded;

	expanded = NULL;
	expand.count = 0;
	if (!_init_expand(&expand, split))
		return (NULL);
	while (split->parse->cmdstr < split->end
		&& split->parse->shell_state->status == SUCCESS)
	{
		if (split->parse->cmdstr == split->tag)
			_extract_tag(&expand, split);
		else if ((split->tag && split->parse->cmdstr < split->tag)
			|| (!split->tag && split->parse->cmdstr < split->end))
			_extract_word(&expand, split);
	}
	if (split->parse->shell_state->status == SUCCESS)
		expanded = _join_strs(&expand);
	ft_free_strarr(expand.strs);
	return (expanded);
}

int	_init_expand(t_expand *expand, t_split *split)
{
	char	*str;

	str = split->parse->cmdstr;
	while (str < split->end)
	{
		expand->count++;
		if (*str == '$')
		{
			str++;
			while (ft_isalnum(*str) || *str == '_')
				str++;
		}
		else
		{
			while (str < split->end && *str != '$')
				str++;
		}
	}
	expand->strs = ft_calloc(expand->count + 1, sizeof(*expand->strs));
	expand->count = 0;
	if (!expand->strs)
		return (0);
	return (1);
}

static	void	_extract_tag(t_expand *expand, t_split *split)
{
	size_t	len;
	char	*ename;
	char	*evalue;

	split->tag++;
	split->parse->cmdstr++;
	len = 0;
	while (ft_isalnum(split->tag[len]) || split->tag[len] == '_')
		len++;
	ename = ft_substr(split->tag, 0, len);
	if (!ename)
		return (update_status(split->parse->shell_state, MALLOC_ERROR));
	evalue = getenvp_value(split->parse->shell_state, ename);
	if (evalue)
		expand->strs[expand->count] = ft_strdup(evalue);
	else
		expand->strs[expand->count] = ft_strdup("");
	free(ename);
	if (!expand->strs[expand->count])
		return (update_status(split->parse->shell_state, MALLOC_ERROR));
	expand->count++;
	split->tag = ft_strchr(split->parse->cmdstr, '$');
	if (split->tag > split->end)
		split->tag = NULL;
	split->parse->cmdstr += len;
}

static void	_extract_word(t_expand *expand, t_split *split)
{
	size_t	len;

	len = 0;
	if (split->tag)
	{
		while (&split->parse->cmdstr[len] != split->tag)
			len++;
	}
	else
	{
		while (&split->parse->cmdstr[len] != split->end)
			len++;
	}
	expand->strs[expand->count] = ft_substr(split->parse->cmdstr, 0, len);
	if (!expand->strs[expand->count])
		return (update_status(split->parse->shell_state, MALLOC_ERROR));
	expand->count++;
	split->parse->cmdstr += len;
}

static char	*_join_strs(t_expand *expand)
{
	size_t	i;
	char	*tmp;
	char	*joined;

	i = 0;
	joined = NULL;
	while (i < expand->count)
	{
		if (expand->strs[i][0])
		{
			tmp = ft_strjoin(joined, expand->strs[i]);
			if (!tmp)
				return (NULL);
			free(joined);
			joined = tmp;
		}
		i++;
	}
	if (!joined)
		joined = ft_strdup("");
	return (joined);
}
