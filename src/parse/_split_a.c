/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split_a.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 15:05:45 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/16 13:55:31 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_init_split(t_parse *parse, t_split *split);
static void	_count_split(char *line, t_split *split);
static void	_do_split(t_split *split);

char	**_split(t_parse *parse)
{
	t_split	split;

	_init_split(parse, &split);
	_count_split(parse->cmdstr, &split);
	if (parse->status != SUCCESS)
		return (NULL);
	split.result = ft_calloc(split.count + 1, sizeof(*split.result));
	split.count = 0;
	if (!split.result)
		parse->status = MALLOC_ERROR;
	else
		_do_split(&split);
	if (parse->status == SUCCESS)
		return (split.result);
	ft_free_strarr(split.result);
	return (NULL);
}

static void	_init_split(t_parse *parse, t_split *split)
{
	split->count = 0;
	split->line = parse->cmdstr;
	split->pos = NULL;
	split->tag = NULL;
	split->tmp = NULL;
	split->result = NULL;
	split->status = &parse->status;
	split->pathv = parse->shell_state->env_pathv;
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

static void	_do_split(t_split *split)
{
	while (split->status == SUCCESS && split->line && *(split->line))
	{
		while (ft_isspace(*split->line))
			split->line++;
		if (ft_isquote(*(split->line)) == 1)
			_extract_quote_literal(split);
		else if (ft_isquote(*split->line) == 2)
			_extract_quote_expand(split);
		else if (*split->line)
			_extract_word(split);
	}
	// split->result[split->count] = NULL;
}
