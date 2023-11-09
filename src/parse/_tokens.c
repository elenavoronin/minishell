/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _tokens.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/09 14:02:39 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_token_type(char *c);
static void	_populate_cmd(size_t *i, t_parse *parse);
static void	_populate_cmdtable(t_parse *parse);

void	_tokens_to_cmd(t_parse *parse)
{
	size_t	i;

	parse->tokens = ft_split2(parse->cmdstr);
	if (!parse->tokens)
	{
		_malloc_error(parse);
		return ;
	}
	i = 0;
	parse->rem = ft_strarray_count(parse->tokens);
	parse->count = parse->rem;
	while (parse->tokens[i] && !parse->status)
	{
		_populate_cmd(&i, parse);
		i++;
	}
	parse->count = 0;
	if (parse->rem)
		_populate_cmdtable(parse);
}

static void	_populate_cmd(size_t *i, t_parse *parse)
{
	char	**dest_address;

	dest_address = NULL;
	if (_token_type(parse->tokens[*i]) == REDIR_HERE)
		dest_address = &(parse->cmd->delimiter);
	else if (_token_type(parse->tokens[*i]) == REDIR_IN)
		dest_address = &(parse->cmd->infile);
	else if (_token_type(parse->tokens[*i]) == REDIR_OUT)
		dest_address = &(parse->cmd->outfile);
	else if (_token_type(parse->tokens[*i]) == REDIR_APPEND)
		parse->cmd->output_flag = 'a';
	if (dest_address)
	{
		*i += 1;
		parse->rem--;
		if (*i < parse->count)
		{
			*dest_address = ft_strdup(parse->tokens[*i]);
			free(parse->tokens[*i]);
			parse->tokens[*i] = NULL;
			parse->rem--;
		}
		else
			parse->status = SYNTAX_ERROR;
	}
}

static void	_populate_cmdtable(t_parse *parse)
{
	int	i;

	parse->cmd->cmd_table = malloc((parse->rem + 1) * sizeof(char **));
	if (!parse->cmd->cmd_table)
	{
		_malloc_error(parse);
		return ;
	}
	i = 0;
	while (parse->rem)
	{
		if (parse->tokens[parse->count])
		{
			parse->cmd->cmd_table[i] = ft_strdup(parse->tokens[parse->count]);
			if (!parse->cmd->cmd_table[i])
			{
				_malloc_error(parse);
				return ;
			}
			i++;
			parse->rem--;
		}
		parse->count++;
	}
	parse->cmd->cmd_table[i] = NULL;
}

static int	_token_type(char *c)
{
	if (*c == '<')
	{
		if (*(c + 1) == '<')
			return (REDIR_HERE);
		return (REDIR_IN);
	}
	if (*c == '>')
	{
		if (*(c + 1) == '>')
			return (REDIR_APPEND);
		return (REDIR_OUT);
	}
	return (WORD);
}
