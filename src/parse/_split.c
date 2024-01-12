/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 15:05:45 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/12 13:34:43 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	_count_split(char *line, t_split *split);
static void	_do_split(t_split *split);
static void	_extract(t_split *split);
static void	_extract_expand(t_split *split);

char	**_split(t_parse *parse)
{
	t_split	split;

	split.parse = parse;
	_expand(&split); //expand tags where necesary first, then split on spaces
	_count_split(parse->cmdstr, &split);
	if (parse->shell->status != SUCCESS)
		return (NULL);
	split.result = ft_calloc(split.count + 1, sizeof(*split.result));
	split.count = 0;
	if (!split.result)
		parse->shell->status = MALLOC_ERROR;
	else
		_do_split(&split);
	if (parse->shell->status == SUCCESS)
		return (split.result);
	ft_free_strarr(split.result);
	return (NULL);
}

static void	_count_split(char *line, t_split *split)
{
	split->count = 0;
	while (line && *line)
	{
		while (ft_isspace(*line))
			line++;
		if (*line)
		{
			split->count++;
			while (*line && !ft_isspace(*line) && !ft_isquote(*line))
				line++;
			if (ft_isquote(*line))
			{
				line = ft_strchr(line + 1, *line);
				if (!line)
				{
					split->parse->shell->status = SYNTAX_ERROR;
					ft_perror("🐢shell", "syntax error", "Unclosed brackets.");
					return ;
				}
				line++;
			}
			while (*line && !ft_isspace(*line) && !ft_isquote(*line))
				line++;
		}
	}
}

static void	_do_split(t_split *split)
{
	while (split->parse->shell->status == SUCCESS
		&& *(split->parse->cmdstr))
	{
		while (ft_isspace(*split->parse->cmdstr))
			split->parse->cmdstr++;
		if (*(split->parse->cmdstr))
		{
			_extract(split);
			split->count++;
		}
	}
}

static void	_extract(t_split *split)
{
	split->quote = ft_isquote(*(split->parse->cmdstr));
	split->tag = ft_strchr(split->parse->cmdstr, '$');
	if (split->quote)
	{
		split->end = ft_strchr(split->parse->cmdstr + 1, *split->parse->cmdstr);
		split->parse->cmdstr++;
		_extract_expand(split); //here
		split->parse->cmdstr++;
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
	char	*extract;

	if (split->tag > split->end || split->quote == 1)
		split->tag = NULL;
	if (split->tag)
		_expand(split); //here2
	else
	{
		len = split->end - split->parse->cmdstr;
		extract = ft_substr(split->parse->cmdstr, 0, len);
		if (!extract)
			return (update_status(split->parse->shell, MALLOC_ERROR));
		split->result[split->count] = ft_strjoin(split->result[split->count], extract);
		free(extract);
		split->parse->cmdstr = split->end;
	}
	if (!split->result[split->count])
		return (update_status(split->parse->shell, MALLOC_ERROR));
}
