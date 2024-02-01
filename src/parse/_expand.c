/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _expand.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 13:53:26 by dliu          #+#    #+#                 */
/*   Updated: 2024/02/01 21:24:49 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	__expand_env(t_parse *parse, t_shell *shell);
static int	__expand_status(t_parse *parse, t_shell *shell);
static int	__expand_nothing(t_parse *parse, t_shell *shell);

int	_expand(t_shell *shell, t_parse *parse)
{
	parse->pos++;
	if (ft_isalpha(*parse->pos) || *parse->pos == '_')
		return (__expand_env(parse, shell));
	if (*parse->pos == '?')
		return (__expand_status(parse, shell));
	__expand_nothing(parse, shell);
	return (shell->status);
}

static int	__expand_env(t_parse *parse, t_shell *shell)
{
	char	*name;
	char	*value;

	parse->str = parse->pos;
	while (ft_isalpha(*parse->pos) || *parse->pos == '_')
		parse->pos++;
	name = ft_substr(parse->str, 0, parse->pos - parse->str);
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
	_copy_str(shell, parse, value);
	parse->str = parse->pos;
	return (SUCCESS);
}

static int	__expand_status(t_parse *parse, t_shell *shell)
{
	char	*value;

	parse->pos++;
	value = ft_itoa(shell->return_value);
	if (!value)
		return (update_status(shell, MALLOC_ERROR));
	_copy_str(shell, parse, value);
	parse->str = parse->pos;
	return (SUCCESS);
}

static int	__expand_nothing(t_parse *parse, t_shell *shell)
{
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (update_status(shell, MALLOC_ERROR));
	_copy_str(shell, parse, tmp);
	parse->str = parse->pos;
	return (SUCCESS);
}
