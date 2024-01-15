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
static int	_check_quote(t_parse *parse, t_shell *shell);
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
		ft_perror("🐢shell", NULL, "syntax error near unexpected token `|'");
		return (update_status(shell, SYNTAX_ERROR));
	}
	if (_extract_cmdstr(&parse, shell) != SUCCESS)
	{
		free(parse.cmdstr);
		return (shell->status);
	}
	tokens = ft_split2(parse.cmdstr);
	free(parse.cmdstr);
	if (!tokens)
		return (update_status(shell, MALLOC_ERROR));
	_tokenise(tokens, shell);
	ft_free_strarr(tokens);
	return (SUCCESS);
}

static int	_extract_cmdstr(t_parse *parse, t_shell *shell)
{
	parse->cmdstr = NULL;
	parse->quote = 0;
	while (*parse->line && shell->status == SUCCESS)
	{
		if (ft_isquote(*parse->line))
			_check_quote(parse, shell);
		else if (*parse->line == '$')
			_expand(parse, shell);
		else
		{
			parse->pos = parse->line;
			while (*parse->pos
				&& !ft_isquote(*parse->pos) && *parse->pos != '$')
				parse->pos++;
		}
		if (shell->status == SUCCESS && parse->pos > parse->line)
			_join_cmdstr(parse, shell);
	}
	printf("extracted line = %s\n", parse->cmdstr);
	return (shell->status);
}

static int	_check_quote(t_parse *parse, t_shell *shell)
{
	parse->pos = parse->line + 1;
	if (parse->quote)
	{
		parse->quote = 0;
		return (SUCCESS);
	}
	parse->quote = ft_isquote(*parse->line);
	parse->quote_end = ft_strchr(parse->pos, *(parse->line));
	if (!parse->quote_end)
	{
		ft_perror("🐢shell", "parsing", "Ew, close your quotes when you type");
		return (update_status(shell, SYNTAX_ERROR));
	}
	if (parse->quote == 1)
		parse->pos = parse->quote_end + 1;
	else
	{
		parse->pos = parse->line;
		while (parse->pos < parse->quote_end && *parse->pos != '$')
			parse->pos++;
	}
	return (SUCCESS);
}

static int	_join_cmdstr(t_parse *parse, t_shell *shell)
{
	char	*join;
	char	*old;

	join = ft_substr(parse->line, 0, parse->pos - parse->line);
	if (!join)
		return (update_status(shell, MALLOC_ERROR));
	old = parse->cmdstr;
	parse->cmdstr = ft_strjoin(old, join);
	free(old);
	free(join);
	if (!parse->cmdstr)
		return (update_status(shell, MALLOC_ERROR));
	parse->line = parse->pos;
	return (SUCCESS);
}

void	delete_cmd(void *content)
{
	t_cmd	*cmd;

	if (content)
	{
		cmd = content;
		ft_free_strarr(cmd->cmd_table);
		free(cmd->delimiter);
		free(cmd->infile);
		free(cmd->outfile);
		free(cmd);
	}
}
