/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _handle_symbols.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:48:52 by dliu          #+#    #+#                 */
/*   Updated: 2024/02/02 07:04:18 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__handle_in(t_shell *shell, t_parse *parse);
static int	__handle_out(t_shell *shell, t_parse *parse);
static int	__handle_pipe(t_shell *shell, t_parse *parse);

int	_handle_symbols(t_shell *shell, t_parse *parse)
{
	if (*parse->pos == '<')
		return (__handle_in(shell, parse));
	if (*parse->pos == '>')
		return (__handle_out(shell, parse));
	if (*parse->pos == '|')
		return (__handle_pipe(shell, parse));
	write(STDERR_FILENO, "WHY NO SYMBOL?", 14);
	return (update_status(shell, INTERNAL_ERROR));
}

static int	__handle_in(t_shell *shell, t_parse *parse)
{
	parse->str = parse->pos;
	parse->pos += ft_charcount(parse->pos, *parse->pos);
	if (parse->pos - parse->str == 1)
		parse->tokens[parse->i] = IN;
	else if (parse->pos - parse->str == 2)
		parse->tokens[parse->i] = HERE;
	if (parse->pos - parse->str > 2 || parse->i == parse->count - 1
		|| ((parse->i > 0 && parse->tokens[parse->i - 1] != ARG
				&& parse->tokens[parse->i - 1] != PIPE)))
	{
		ft_perror("🐢shell", NULL, "syntax error near redirect in");
		return (update_status(shell, SYNTAX_ERROR));
	}
	return (_copy_fin(shell, parse));
}

static int	__handle_out(t_shell *shell, t_parse *parse)
{
	parse->str = parse->pos;
	parse->pos += ft_charcount(parse->pos, *parse->pos);
	if (parse->pos - parse->str == 1)
		parse->tokens[parse->i] = OUT;
	else if (parse->pos - parse->str == 2)
		parse->tokens[parse->i] = APPEND;
	if (parse->pos - parse->str > 2 || parse->i == parse->count - 1
		|| ((parse->i > 0 && parse->tokens[parse->i - 1] != ARG
				&& parse->tokens[parse->i - 1] != PIPE)))
	{
		ft_perror("🐢shell", NULL, "syntax error near redirect out");
		return (update_status(shell, SYNTAX_ERROR));
	}
	return (_copy_fin(shell, parse));
}

static int	__handle_pipe(t_shell *shell, t_parse *parse)
{
	parse->str = parse->pos;
	parse->pos += ft_charcount(parse->pos, *parse->pos);
	if (parse->pos - parse->str == 1)
		parse->tokens[parse->i] = PIPE;
	if (parse->pos - parse->str > 1 || parse->i == 0
		|| parse->i == parse->count - 1
		|| ((parse->i > 0 && parse->tokens[parse->i - 1] == PIPE)))
	{
		ft_perror("🐢shell", NULL, "syntax error near pipe");
		return (update_status(shell, SYNTAX_ERROR));
	}
	return (_copy_fin(shell, parse));
}
