/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _tokens.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/13 16:55:02 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_populate_cmd(t_parse *parse);
static void	_populate_cmdtable(char *token, t_parse *parse);
static int	_token_type(char *c);
static char	**_get_dest(char *token, t_parse *parse);

void	_tokens_to_cmd(t_parse *parse)
{
	char	**tokens;

	tokens = ft_split2(parse->cmdstr);
	if (!tokens)
	{
		parse->status = MALLOC_ERROR;
		return ;
	}
	parse->tokens = tokens;
	_populate_cmd(parse);
	ft_free_strarr(tokens);
}

static int	_populate_cmd(t_parse *parse)
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
				return (0);
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
	return (1);
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

static char	**_get_dest(char *token, t_parse *parse)
{
	int		token_type;
	char	**dest;

	dest = NULL;
	token_type = _token_type(token);
	if (token_type == REDIR_HERE)
		dest = &(parse->cmd->delimiter);
	else if (token_type == REDIR_IN)
		dest = &(parse->cmd->infile);
	else if (token_type == REDIR_OUT)
		dest = &(parse->cmd->outfile);
	else if (token_type == REDIR_APPEND)
	{
		parse->cmd->output_flag = 'a';
		dest = &(parse->cmd->outfile);
	}
	else if (token_type == WORD)
	{
		parse->argc++;
		dest = &(parse->cmd->cmd_table[0]);
	}
	return (dest);
}

static int	_token_type(char *c)
{
	if (!c)
		return (EMPTY);
	if (ft_strncmp(c, "<", 2) == 0)
		return (REDIR_IN);
	else if (ft_strncmp(c, "<<", 3) == 0)
		return (REDIR_HERE);
	else if (ft_strncmp(c, ">", 2) == 0)
		return (REDIR_OUT);
	else if (ft_strncmp(c, ">>", 3) == 0)
		return (REDIR_APPEND);
	return (WORD);
}
