/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _expand.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 13:53:26 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/15 16:01:50 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	_expand_status(t_parse *parse, t_shell *shell);
static int	_expand_env(t_parse *parse, t_shell *shell);

int	_expand(t_parse *parse, t_shell *shell)
{
	parse->line++;
	if (!ft_isalpha(*parse->line) && *parse->line != '_' && *parse->line != '?')
		return (SUCCESS);
	if (*parse->line == '?')
		return (_expand_status(parse, shell));
	else
		return (_expand_env(parse, shell));
}

static int	_expand_status(t_parse *parse, t_shell *shell)
{
	char	*value;

	parse->line++;
	value = ft_itoa(shell->return_value);
	if (!value)
		return (update_status(shell, MALLOC_ERROR));
	parse->cmdstr = ft_strcat_free(parse->cmdstr, value);
	if (!parse->cmdstr)
		return (update_status(shell, MALLOC_ERROR));
	return (SUCCESS);
}

static int	_expand_env(t_parse *parse, t_shell *shell)
{
	char	*name;
	char	*value;

	parse->pos = parse->line;
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
	name = parse->cmdstr;
	parse->cmdstr = ft_strjoin(name, value);
	free(name);
	free(value);
	if (!parse->cmdstr)
		return (update_status(shell, MALLOC_ERROR));
	parse->line = parse->pos;
	return (SUCCESS);
}
