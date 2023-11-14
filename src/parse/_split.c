/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 15:05:45 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/14 17:59:19 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_init_split(t_code_status *status, t_split *split)
{
	split->status = status;
	split->quoted = NO_Q;
	split->count = 0;
	split->pos = NULL;
	split->result = NULL;
}

static void	_syntax_error(t_split *split)
{
	*(split->status) = SYNTAX_ERROR;
	ft_perror("SYNTAX ERROR", NULL, "Unclosed brackets found.");
}

static void	_count_split(char *line, t_split *split)
{
	while (*(split->status) == SUCCESS && line && *line)
	{
		while (*line && ft_isspace(*line))
			line++;
		if (ft_isquote(*line))
		{
			split->count++;
			line = ft_strchr(line + 1, *line);
			if (!line)
				_syntax_error(split);
			else
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

char	**_split_and_expand(char *line, t_code_status *status)
{
	t_split	split;

	if (!line)
		return (NULL);
	_init_split(status, &split);
	_count_split(line, &split);
	if (*status != SUCCESS)
		return (NULL);
	printf("COUNT = %zu\n", split.count);
	*status = SYNTAX_ERROR;
	return (split.result);
}

// static char	*_split(char *line, t_split *split)
// {
// }

// static char	*_expand(char *line)
// {
// }
