/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split_a.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 15:05:45 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/17 15:09:28 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_init_split(t_status_code *status, t_split *split);
static void	_count_split(char *line, t_split *split);
static void	_do_split(char *line, t_split *split);

char	**_split(char *line, t_status_code *status)
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

static void	_init_split(t_status_code *status, t_split *split)
{
	split->status = status;
	split->count = 0;
	split->pos = NULL;
	split->result = NULL;
}

static void	_count_split(char *line, t_split *split)
{
	while (line && *line)
	{
		while (ft_isspace(*line))
			line++;
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

static void	_do_split(char *line, t_split *split)
{
	while (line && *line)
	{
		while (ft_isspace(*line))
			line++;
		line += _extract_quote_literal(line, split);
		line += _extract_quote_expand(line, split);
		line += _extract_word(line, split);
		if (*(split->status) != SUCCESS)
			return ;
	}
	split->result[split->count] = NULL;
}
