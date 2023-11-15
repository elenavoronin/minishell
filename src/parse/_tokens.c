/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _tokens.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/15 12:44:11 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_populate_cmd(t_parse *parse);
static void	_populate_cmdtable(char *token, t_parse *parse);
static char	**_get_dest(char *token, t_parse *parse);

void	_tokens_to_cmd(t_parse *parse)
{
	char	**tokens;

	tokens = _split(parse->cmdstr, &(parse->status));
	free(parse->cmdstr);
	if (parse->status != SUCCESS)
		return ;
	parse->tokens = tokens;
	_populate_cmd(parse);
	ft_free_strarr(tokens);
}

static void	_populate_cmd(t_parse *parse)
{
	char	**dest;

	while (*parse->tokens && !parse->status)
	{
		dest = _get_dest(*parse->tokens, parse);
		if (dest && *dest != parse->cmd->cmd_table[0])
		{
			parse->tokens++;
			if (!*(parse->tokens))
			{
				parse->status = SYNTAX_ERROR;
				return ;
			}
			if (*dest)
				free(*dest);
			*dest = ft_strdup(*parse->tokens);
			if (!*dest)
				parse->status = MALLOC_ERROR;
		}
		else if (dest == &parse->cmd->cmd_table[0])
			_populate_cmdtable(*parse->tokens, parse);
		parse->tokens++;
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
	else
	{
		parse->argc++;
		dest = &(parse->cmd->cmd_table[0]);
	}
	return (dest);
}

static void	_populate_cmdtable(char *token, t_parse *parse)
{
	char	**cmdtable;
	size_t	i;

	cmdtable = ft_malloc_wrapper((parse->argc + 1) * sizeof(*cmdtable));
	if (!cmdtable)
	{
		parse->status = MALLOC_ERROR;
		return ;
	}
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
