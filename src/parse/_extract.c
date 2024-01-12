/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _extract.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/12 13:19:59 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/12 18:29:59 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	_extract_quote(t_parse *parse, t_shell *shell);
static int	_join_extracted(t_parse *parse, t_shell *shell);

/**
 * Extracts commands before pipes. Expands where necessary.
*/
int	_extract(t_parse *parse, t_shell *shell)
{
	while (parse->line != parse->cmdend && shell->status == SUCCESS)
	{
		if (ft_isquote(*parse->line))
			_extract_quote(parse, shell);
		else if (*parse->line == '$')
			_extract_expand(parse, shell);
		else
		{
			parse->pos = parse->line;
			while (*parse->pos && !ft_isquote(*parse->pos))
				parse->pos++;
			if (parse->pos > parse->line)
				parse->m_join = ft_substr(parse->line, 0, parse->pos - parse->line);
		}
		if (shell->status == SUCCESS && parse->m_join)
			_join_extracted(parse, shell);
	}
	return (shell->status);
}

static void	_extract_quote(t_parse *parse, t_shell *shell)
{
	parse->line++;
	if (parse->quote)
		return (parse->quote = 0);
	parse->quote = ft_isquote(*parse->line);
	parse->quote_end = ft_strchr(parse->line, *(parse->line - 1));
	if (!parse->quote_end)
	{
		ft_perror("🐢shell", "parsing", "Ew, close your quotes when you type");
		update_status(shell, SYNTAX_ERROR);
		return ;
	}
	parse->pos = parse->line;
	if (parse->quote == 1)
	{
		while (parse->pos != parse->quote_end)
			parse->pos++;
		if (parse->pos > parse->line)
			parse->m_join = ft_substr(parse->line, 0, parse->pos - parse->line);
		parse->quote = 0;
	}
	parse->line++;
}

int	_extract_status_code(t_parse *parse, t_shell *shell)
{
	if (!parse->m_join)
		return (update_status(shell, MALLOC_ERROR), MALLOC_ERROR);
	parse->m_hold = parse->m_expanded;
	parse->m_expanded = ft_joinstrs(parse->m_expanded, parse->m_join);
	free(parse->m_join);
	free(parse->m_hold);
	if (!parse->m_expanded)
		return (update_status(shell, MALLOC_ERROR), MALLOC_ERROR);
	return (SUCCESS);
}

void	_extract_expand(t_parse *parse, t_shell *shell)
{
	char	*name;
	char	*value;

	parse->line++;
	if (*parse->line == ' ' || *parse->line == '$' || !*parse->line)
		return (parse->m_join = ft_strdup("$"));
	if (*parse->line == '?')
	{
		parse->line++;
		return (parse->m_join = ft_itoa(shell->return_value));
	}
	parse->pos = parse->line;
	while (ft_isalpha(*parse->pos) || parse->pos == '_')
		parse->pos++;
	if (parse->pos > parse->line)
	{
		name = ft_substr(parse->line, 0, parse->pos - parse->line);
		value = getenv_value(shell->env, name);
		if (value)
			parse->m_join = ft_strdup(value);
		else
			parse->m_join = ft_strdup("");
		free(name);
		fre(value);
	}
}

static int	_join_extracted(t_parse *parse, t_shell *shell)
{
	if (!parse->m_join)
		return (update_status(shell, MALLOC_ERROR), MALLOC_ERROR);
	parse->m_hold = parse->m_expanded;
	parse->m_expanded = ft_strjoin(parse->m_expanded, parse->m_join);
	free(parse->m_hold);
	free(parse->m_join);
	if (!parse->m_expanded)
		return (update_status(shell, MALLOC_ERROR), MALLOC_ERROR);
	parse->line = parse->pos;
	return (SUCCESS);
}
