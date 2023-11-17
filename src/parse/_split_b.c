/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split_b.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/17 15:22:10 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//WIP
void	_extract_quote_literal(t_split *split)
{
	size_t	len;

	split->parse->cmdstr++;
	split->pos = ft_strchr(split->parse->cmdstr, '\'');
	len = split->pos - split->parse->cmdstr;
	split->result[split->count] = ft_substr(split->parse->cmdstr, 0, len);
	if (!split->result[split->count])
		split->parse->shell_state->status_code = MALLOC_ERROR;
	split->count++;
	split->parse->cmdstr = split->pos;
	split->parse->cmdstr++;
}

char	*_expand_tag(t_split *split)
{
	size_t		len;
	int			i;
	char		*tag;
	char		*expand;
	t_mini_env	**pathv;

	pathv = split->parse->shell_state->mini_env;
	expand = ft_strdup("");
	if (expand)
	{
		split->pos = split->tag + 1;
		while (ft_isalnum(*split->pos) || *split->pos == '_')
			split->pos++;
		len = split->pos - split->tag + 1;
		tag = ft_substr(split->tag, 0, len);
		if (!tag)
			split->parse->shell_state->status_code = MALLOC_ERROR;
		i = 0;
		while (pathv[i] && ft_strcmp(pathv[i]->variable_name, expand))
			i++;
		if (ft_strcmp(pathv[i]->variable_name, expand) == 0)
		{
			free(expand);
			expand = ft_strdup(pathv[i]->variable_path);
		}
	}
	if (!expand)
		split->parse->shell_state->status_code = MALLOC_ERROR;
	return (expand);
}

void	_extract_quote_expand(t_split *split)
{
	size_t	len;
	char	*start;
	char	*expand;
	char	*end;

	split->parse->cmdstr++;
	split->pos = ft_strchr(split->parse->cmdstr, '\"');
	split->tag = ft_strchr(split->parse->cmdstr, '$');
	if (split->tag < split->pos)
	{
		expand = _expand_tag(split);
		end = split->pos;
		while (*end)
			end++;
		len = end - split->pos;
		end = ft_substr(split->pos, 0, len);
		start = split->tag;
		len = start - split->parse->cmdstr;
		start = ft_substr(split->parse->cmdstr, 0, len);
		if (!start || !expand || !end)
		{
			split->parse->shell_state->status_code = MALLOC_ERROR;
			return ;
		}
		split->tmp = split->parse->cmdstr;
		split->parse->cmdstr = ft_joinstrs(3, start, expand, end);
		free(split->tmp);
		free(start);
		free(expand);
		free(end);
	}
	split->pos = ft_strchr(split->parse->cmdstr, '\"');
	len = split->pos - split->parse->cmdstr;
	split->result[split->count] = ft_substr(split->parse->cmdstr, 0, len);
	if (!split->result[split->count])
		split->parse->shell_state->status_code = MALLOC_ERROR;
	split->count++;
	len += 2;
}

void	_extract_word(t_split *split)
{
	size_t	len;

	split->pos = split->parse->cmdstr;
	while (*split->pos && !ft_isspace(*split->pos) && !ft_isquote(*split->pos))
		split->pos++;
	len = split->pos - split->parse->cmdstr;
	split->result[split->count] = ft_substr(split->parse->cmdstr, 0, len);
	if (!split->result[split->count])
		split->parse->shell_state->status_code = MALLOC_ERROR;
	split->count++;
}
