/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 15:05:45 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/14 19:10:53 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_init_split(t_code_status *status, t_split *split)
{
	split->status = status;
	split->count = 0;
	split->pos = NULL;
	split->result = NULL;
}

static void	_count_split(char *line, t_split *split)
{
	while (*(split->status) == SUCCESS && line && *line)
	{
		line += ft_charcount(line, ' ');
		if (ft_isquote(*line))
		{
			split->count++;
			line = ft_strchr(line + 1, *line);
			if (!line)
			{
				*(split->status) = SYNTAX_ERROR;
				ft_perror("SYNTAX ERROR", NULL, "Unclosed brackets found.");
				return ;
			}
			line++;
		}
		else if (*line && !ft_isspace(*line) && !ft_isquote(*line))
		{
			split->count++;
			while (*line && !ft_isspace(*line) && !ft_isquote(*line))
				line++;
		}
	}
}

char	**_split(char *line, t_code_status *status)
{
	t_split	split;

	if (!line)
		return (NULL);
	_init_split(status, &split);
	_count_split(line, &split);
	if (*status != SUCCESS)
		return (NULL);
	split.result = ft_calloc(split.count + 1, sizeof(*split.result));
	split.count = 0;
	if (!split.result)
		*status = MALLOC_ERROR;
	else
		_do_split(line, &split);
	if (*status == SUCCESS)
		return (split.result);
	ft_free_strarr(split.result);
	return (NULL);
}

static int	_extract_quote_literal(char *line, t_split *split)
{
	int	len;

	len = 0;
	if (ft_isquote(*line) == 1)
	{
		split->pos = ft_strchr(split->pos, '\'');
		len = split->pos - line;
		split->result[split->count] = ft_substr(line, 0, len);
		if (!split->result[split->count])
			*(split->status) = MALLOC_ERROR;
		split->count++;
	}
	return (len);
}

static int	_extract_quote_expand(char *line, t_split *split)
{
	int	len;

	len = 0;
	if (ft_isquote(*line) == 2)
	{
		split->pos = ft_strchr(split->pos, '\"');
		len = split->pos - line;
		split->result[split->count] = ft_substr(line, 0, len);
		if (!split->result[split->count])
			*(split->status) = MALLOC_ERROR;
		split->count++;
	}
	return (len);
}

static int	_extract_word(char *line, t_split *split)
{
	char	*pos;
	size_t	len;

	pos = line;
	while (pos && *pos && !ft_isspace(*pos) && !ft_isquote(*pos))
		pos++;
	len = pos - line;
	split->result[split->count] = ft_substr(line, 0, len);
	if (!split->result[split->count])
		*(split->status) = MALLOC_ERROR;
	split->count++;
	return (len);
}

static void	_do_split(char *line, t_split *split)
{
	while (*(split->status) == SUCCESS && line && *line)
	{
		line += ft_charcount(line, ' ');
		line += _extract_quote_literal(++line, split);
		line += _extract_quote_expand(++line, split);
		line += _extract_word(line, split);
		if (*(split->status) != SUCCESS)
			return ;
	}
}
