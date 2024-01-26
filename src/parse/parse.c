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

static int	_extract_cmdstr(t_parse *parse, t_shell *shell);
static int	_handle_quotes(t_parse *parse, t_shell *shell);
static int	_expand_in_quotes(t_parse *parse, t_shell *t_shell);
static int	_join_cmdstr(t_parse *parse, t_shell *shell);

/**
 * Parses shell->line. Allocates memory for linked list and content.
 * @return On success, returns pointer to head of list.
*/
int	parse_input(t_shell *shell)
{
	t_parse	parse;
	char	**tokens;

	parse.line = shell->line;
	while (ft_isspace(*parse.line))
		parse.line++;
	if (*parse.line == '|')
	{
		ft_perror("🐢shell", "syntax error",
			"syntax error near unexpected token `|'");
		return (update_status(shell, SYNTAX_ERROR));
	}
	if (_extract_cmdstr(&parse, shell) != SUCCESS)
	{
		free(parse.cmdstr);
		return (shell->status);
	}
	tokens = _split(parse.cmdstr);
	free(parse.cmdstr);
	if (!tokens)
		return (update_status(shell, MALLOC_ERROR));
	_tokenise(tokens, shell);
	ft_free_strarr(tokens);
	return (shell->status);
}

static int	_extract_cmdstr(t_parse *parse, t_shell *shell)
{
	parse->cmdstr = NULL;
	parse->pos = parse->line;
	while (*parse->line && shell->status == SUCCESS)
	{
		if (ft_isquote(*parse->line))
			_handle_quotes(parse, shell);
		else if (*parse->line == '$')
			_expand(parse, shell);
		while (*parse->pos && !ft_isquote(*parse->pos) && *parse->pos != '$')
		{
			if ((*parse->pos == '>' || *parse->pos == '<')
				&& ft_charcount(parse->pos, *parse->pos) > 2)
			{
				ft_perror("🐢shell", "syntax error",
					"Pay attention to your angle brackets!");
				return (update_status(shell, SYNTAX_ERROR));
			}
			parse->pos++;
		}
		if (shell->status == SUCCESS && parse->pos > parse->line)
			_join_cmdstr(parse, shell);
	}
	return (shell->status);
}

static int	_handle_quotes(t_parse *parse, t_shell *shell)
{
	int		qtype;
	char	*qend;

	qtype = ft_isquote(*parse->line);
	parse->pos = parse->line + 1;
	qend = ft_strchr(parse->pos, *(parse->line));
	if (!qend)
	{
		ft_perror("🐢shell", "syntax error",
			"Ew, close your quotes when you type");
		return (update_status(shell, SYNTAX_ERROR));
	}
	if (qtype == 1)
		parse->pos = qend + 1;
	while (parse->pos <= qend)
	{
		if (*parse->pos != '$')
			parse->pos++;
		else if (_expand_in_quotes(parse, shell) != SUCCESS)
			return (shell->status);
	}
	return (_join_cmdstr(parse, shell));
}

static int	_expand_in_quotes(t_parse *parse, t_shell *shell)
{
	if (parse->pos > parse->line)
	{
		if (_join_cmdstr(parse, shell) != SUCCESS)
			return (shell->status);
	}
	return (_expand(parse, shell));
}

static int	_join_cmdstr(t_parse *parse, t_shell *shell)
{
	char	*join;
	char	*old;

	join = ft_substr(parse->line, 0, parse->pos - parse->line);
	if (!join)
		return (update_status(shell, MALLOC_ERROR));
	old = parse->cmdstr;
	parse->cmdstr = ft_strcat_free(old, join);
	if (!parse->cmdstr)
		return (update_status(shell, MALLOC_ERROR));
	parse->line = parse->pos;
	return (SUCCESS);
}
