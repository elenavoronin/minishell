/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split_a.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 15:05:45 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/17 15:25:25 by codespace     ########   odam.nl         */
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
	if (parse->shell_state->status_code != SUCCESS)
		return (NULL);
	split.result = ft_calloc(split.count + 1, sizeof(*split.result));
	split.count = 0;
	if (!split.result)
		parse->shell_state->status_code = MALLOC_ERROR;
	else
		_do_split(&split);
	if (parse->shell_state->status_code == SUCCESS)
		return (split.result);
	ft_free_strarr(split.result);
	return (NULL);
}

static void	_init_split(t_parse *parse, t_split *split)
{
	split->parse = parse;
	split->count = 0;
	split->pos = NULL;
	split->tag = NULL;
	split->tmp = NULL;
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
				split->parse->shell_state->status_code = SYNTAX_ERROR;
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
	t_status_code	*status;

	status = &(split->parse->shell_state->status_code);
	while (*status == SUCCESS && *(split->parse->cmdstr))
	{
		while (ft_isspace(*split->parse->cmdstr))
			split->parse->cmdstr++;
		if (ft_isquote(*(split->parse->cmdstr)) == 1)
			_extract_quote_literal(split);
		else if (ft_isquote(*split->parse->cmdstr) == 2)
			_extract_quote_expand(split);
		else if (*split->parse->cmdstr)
			_extract_word(split);
	}
}
