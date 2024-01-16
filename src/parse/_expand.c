/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _expand.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 13:53:26 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/16 15:55:36 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	_expand_env(t_parse *parse, t_shell *shell);
static int	_expand_status(t_parse *parse, t_shell *shell);
static int	_expand_nothing(t_parse *parse, t_shell *shell);

int	_expand(t_parse *parse, t_shell *shell)
{
	char	*hold;

	hold = parse->cmdstr;
	parse->pos++;
	if (ft_isalpha(*parse->pos) || *parse->pos == '_')
		_expand_env(parse, shell);
	else if (*parse->pos == '?')
		_expand_status(parse, shell);
	else
		_expand_nothing(parse, shell);
	free(hold);
	parse->line = parse->pos;
	return (shell->status);
}

static int	_expand_env(t_parse *parse, t_shell *shell)
{
	char	*name;
	char	*value;

	parse->line = parse->pos;
	while (ft_isalpha(*parse->pos) || *parse->pos == '_')
		parse->pos++;
	name = ft_substr(parse->line, 0, parse->pos - parse->line);
	if (!name)
		return (update_status(shell, MALLOC_ERROR));
	value = getenv_value(shell->env, name);
	free(name);
	if (value)
		value = ft_strdup(value);
	else
		value = ft_strdup("");
	if (!value)
		return (update_status(shell, MALLOC_ERROR));
	parse->cmdstr = ft_strjoin(parse->cmdstr, value);
	free(value);
	if (!parse->cmdstr)
		return (update_status(shell, MALLOC_ERROR));
	return (update_status(shell, SUCCESS));
}

static int	_expand_status(t_parse *parse, t_shell *shell)
{
	char	*value;

	parse->pos++;
	value = ft_itoa(shell->return_value);
	if (!value)
		return (update_status(shell, MALLOC_ERROR));
	parse->cmdstr = ft_strjoin(parse->cmdstr, value);
	free(value);
	if (!parse->cmdstr)
		return (update_status(shell, MALLOC_ERROR));
	return (update_status(shell, SUCCESS));
}

static int	_expand_nothing(t_parse *parse, t_shell *shell)
{
	parse->cmdstr = ft_strjoin(parse->cmdstr, "$");
	if (!parse->cmdstr)
		return (update_status(shell, MALLOC_ERROR));
	return (update_status(shell, SUCCESS));
}
