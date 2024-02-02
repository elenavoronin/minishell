/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   head.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/31 18:04:41 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/02 13:47:38 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static size_t	_count(char *s);
static int		_split(t_shell *shell, t_parse *parse);
static void		_free_parse(t_parse *parse);

/**
 * Parses shell->line. Allocates memory for linked list and content.
 * @return On success, returns pointer to head of list.
*/
int	parse_input(t_shell *shell)
{
	t_parse	parse;

	ft_bzero(&parse, sizeof(parse));
	parse.str = shell->line;
	parse.count = _count(parse.str);
	if (!parse.count)
		return (FAILED);
	parse.result = ft_calloc(parse.count + 1, sizeof(*parse.result));
	parse.tokens = ft_calloc(parse.count, sizeof(*parse.result));
	if (!parse.result || !parse.tokens)
		update_status(shell, MALLOC_ERROR);
	if (_split(shell, &parse) == SUCCESS && parse.result)
		_tokenise(shell, &parse);
	_free_parse(&parse);
	return (shell->status);
}

int	_is_symbol(char c)
{
	if (c == '<')
		return (IN);
	if (c == '>')
		return (OUT);
	if (c == '|')
		return (PIPE);
	return (0);
}

static size_t	_count(char *s)
{
	size_t	count;

	count = 0;
	while (s && *s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s && !_is_symbol(*s))
			count++;
		while (*s && !ft_isspace(*s) && !_is_symbol(*s))
		{
			if (ft_isquote(*s))
				s = ft_strchr(s + 1, *s);
			if (!s)
				return (ft_perror("🐢shell", NULL,
						"Ew, close your quotes when you type"), 0);
			s++;
		}
		if (_is_symbol(*s))
		{
			count++;
			s += ft_charcount(s, *s);
		}
	}
	return (count);
}

static int	_split(t_shell *shell, t_parse *parse)
{
	if (shell->status != SUCCESS)
		return (shell->status);
	parse->i = 0;
	while (*parse->str && shell->status == SUCCESS)
	{
		while (ft_isspace(*parse->str))
			parse->str++;
		if (!parse->str)
			return (shell->status);
		parse->pos = parse->str;
		if (_is_symbol(*parse->pos))
			_handle_symbols(shell, parse);
		else
			_handle_args(shell, parse);
	}
	return (shell->status);
}

static void	_free_parse(t_parse *parse)
{
	ft_free_strarr(parse->result);
	parse->result = NULL;
	free(parse->tmp);
	parse->tmp = NULL;
	free(parse->tokens);
	parse->tokens = NULL;
}
