/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _handle_args.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:48:52 by dliu          #+#    #+#                 */
/*   Updated: 2024/02/01 21:10:29 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	__handle_quote_one(t_shell *shell, t_parse *parse);
static int	__handle_quote_two(t_shell *shell, t_parse *parse);

int	_handle_args(t_shell *shell, t_parse *parse)
{
	parse->str = parse->pos;
	while (shell->status == SUCCESS && *parse->pos
		&& !_is_symbol(*parse->pos) && !ft_isspace(*parse->pos))
	{
		if (*parse->pos == '$')
			_expand(shell, parse);
		else if (*parse->pos == '\'')
			__handle_quote_one(shell, parse);
		else if (*parse->pos == '\"')
			__handle_quote_two(shell, parse);
		else
			parse->pos++;
	}
	if (shell->status == SUCCESS)
	{
		parse->tokens[parse->i] = ARG;
		_copy_fin(shell, parse);
	}
	return (shell->status);
}

static int	__handle_quote_one(t_shell *shell, t_parse *parse)
{
	if (_copy_tmp(shell, parse) != SUCCESS)
		return (shell->status);
	parse->str = parse->pos + 1;
	parse->pos = ft_strchr(parse->str, *parse->pos);
	if (!parse->pos)
	{
		ft_perror("🐢shell", NULL, "Ew, close your quotes when you type");
		return (update_status(shell, SYNTAX_ERROR));
	}
	if (_copy_tmp(shell, parse) != SUCCESS)
		return (shell->status);
	parse->pos++;
	parse->str = parse->pos;
	return (SUCCESS);
}

static int	__handle_quote_two(t_shell *shell, t_parse *parse)
{
	if (_copy_tmp(shell, parse) != SUCCESS)
		return (shell->status);
	parse->str = parse->pos + 1;
	parse->pos = ft_strchr(parse->str, *parse->pos);
	if (!parse->pos)
	{
		ft_perror("🐢shell", NULL, "Ew, close your quotes when you type");
		return (update_status(shell, SYNTAX_ERROR));
	}
	parse->pos = parse->str;
	while (*parse->pos != '\"')
	{
		if (*parse->pos == '$')
			_expand(shell, parse);
		else
			parse->pos++;
	}
	if (_copy_tmp(shell, parse) != SUCCESS)
		return (shell->status);
	parse->pos++;
	parse->str = parse->pos;
	return (SUCCESS);
}
