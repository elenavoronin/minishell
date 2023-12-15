/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _tokens.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/12/15 12:39:51 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	_tokens_to_cmd(char **tokens, t_parse *parse);
static void	_tokens_to_cmdtable(char *token, t_parse *parse);
static char	**_get_dest(char *token, t_parse *parse);

void	_parse_tokens(t_parse *parse)
{
	char	**tokens;
	char	*save_cmdstr;

	save_cmdstr = parse->cmdstr;
	tokens = _split(parse);
	if (parse->shell->status == SUCCESS)
		_tokens_to_cmd(tokens, parse);
	ft_free_strarr(tokens);
	free(save_cmdstr);
}

static void	_tokens_to_cmd(char **tokens, t_parse *parse)
{
	char	**dest;

	while (*tokens)
	{
		dest = _get_dest(*tokens, parse);
		if (dest && *dest != parse->cmd->cmd_table[0])
		{
			tokens++;
			if (!*tokens)
				return (update_status(parse->shell, SYNTAX_ERROR));
			if (*dest)
				free(*dest);
			*dest = ft_strdup(*tokens);
			if (!*dest)
				return (update_status(parse->shell, MALLOC_ERROR));
		}
		else if (dest == &parse->cmd->cmd_table[0])
			_tokens_to_cmdtable(*tokens, parse);
		tokens++;
	}
}

static char	**_get_dest(char *token, t_parse *parse)
{
	char			**dest;

	dest = NULL;
	if (ft_strcmp(token, "<<") == 0)
		dest = &(parse->cmd->delimiter);
	else if (ft_strcmp(token, "<") == 0)
		dest = &(parse->cmd->infile);
	else if (ft_strcmp(token, ">") == 0)
		dest = &(parse->cmd->outfile);
	else if (ft_strcmp(token, ">>") == 0)
	{
		parse->cmd->output_flag = 'a';
		dest = &(parse->cmd->outfile);
	}
	else if (*token)
	{
		parse->argc++;
		dest = &(parse->cmd->cmd_table[0]);
	}
	return (dest);
}

static void	_tokens_to_cmdtable(char *token, t_parse *parse)
{
	char	**cmdtable;
	size_t	i;

	cmdtable = ft_malloc_wrapper((parse->argc + 1) * sizeof(*cmdtable));
	if (!cmdtable)
		return (update_status(parse->shell, MALLOC_ERROR));
	i = 0;
	while (i < parse->argc)
	{
		if (parse->cmd->cmd_table && parse->cmd->cmd_table[i])
			cmdtable[i] = ft_strdup(parse->cmd->cmd_table[i]);
		else
			cmdtable[i] = ft_strdup(token);
		i++;
	}
	cmdtable[i] = NULL;
	ft_free_strarr(parse->cmd->cmd_table);
	parse->cmd->cmd_table = cmdtable;
}
