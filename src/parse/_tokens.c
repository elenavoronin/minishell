/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _tokens.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/10 12:54:40 by dliu          ########   odam.nl         */
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
	parse->cmdstr = NULL;
}

static void	_tokens_to_cmd(char **tokens, t_parse *parse)
{
	char	**dest;

	while (*tokens)
	{
		dest = _get_dest(*tokens, parse);
		if (dest && dest != parse->cmd->cmd_table)
		{
			tokens++;
			if (!*tokens)
			{
				ft_perror("🐢shell", "syntax error", "bad command");
				return (update_status(parse->shell, SYNTAX_ERROR));
			}
			if (*dest)
				free(*dest);
			*dest = ft_strdup(*tokens);
			if (!*dest)
				return (update_status(parse->shell, MALLOC_ERROR));
		}
		else if (*tokens && dest == parse->cmd->cmd_table)
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
		dest = parse->cmd->cmd_table;
	}
	return (dest);
}

static void	_tokens_to_cmdtable(char *token, t_parse *parse)
{
	char	**cmdtable;
	size_t	i;

	cmdtable = ft_calloc((parse->argc + 1), sizeof(*cmdtable));
	if (!cmdtable)
		return (update_status(parse->shell, MALLOC_ERROR));
	i = 0;
	while (i < parse->argc)
	{
		if (parse->cmd->cmd_table && parse->cmd->cmd_table[i])
			cmdtable[i] = ft_strdup(parse->cmd->cmd_table[i]);
		else
			cmdtable[i] = ft_strdup(token);
		if (!cmdtable[i])
			break ;
		i++;
	}
	cmdtable[i] = NULL;
	ft_free_strarr(parse->cmd->cmd_table);
	parse->cmd->cmd_table = cmdtable;
	if (i < parse->argc)
		return (update_status(parse->shell, MALLOC_ERROR));
}
