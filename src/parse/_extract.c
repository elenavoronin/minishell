/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _extract.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/08 18:51:11 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		_token_type(char *c);
void	_validate_str(char *str, t_parse *parse);
void	_tokens_to_cmd(size_t *i, t_parse *parse);
void	_tokens_to_cmdtable(t_parse *parse);

void	_extract_cmdstr(char *input, t_parse *parse)
{
	char	*str;
	size_t	start;

	while (ft_isspace(input[parse->pos]))
		parse->pos++;
	start = parse->pos;
	while (input[parse->pos] && input[parse->pos] != '|')
		parse->pos++;
	str = ft_substr(input, start, parse->pos);
	if (!str)
	{
		_malloc_error(parse);
		parse->cmdstr = NULL;
		return ;
	}
	_validate_str(str, parse);
}

void	_extract_cmd(t_parse *parse)
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
		_tokens_to_cmd(&i, parse);
		i++;
	}
	parse->count = 0;
	_tokens_to_cmdtable(parse);
}

void	_malloc_error(t_parse *parse)
{
	ft_perror("ERROR", "Parsing", "Likely malloc fail.");
	parse->status = MALLOC_ERROR;
}

void	_tokens_to_cmd(size_t *i, t_parse *parse)
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
		*i++;
		if (*i < parse->count)
		{
			dest_address = ft_strdup(parse->tokens[*i]);
			free(parse->tokens[*i]);
			parse->tokens[*i] = NULL;
			parse->rem--;
		}
		else
			parse->status = SYNTAX_ERROR;
	}
}

void	_tokens_to_cmdtable(t_parse *parse)
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

int	_token_type(char *c)
{
	if (*c == '<')
	{
		if (c + 1 == '<')
			return (REDIR_HERE);
		return (REDIR_IN);
	}
	if (c == '>')
	{
		if (c + 1 == '>')
			return (REDIR_APPEND);
		return (REDIR_OUT);
	}
	return (WORD);
}

void	_validate_str(char *str, t_parse *parse)
{
	int	i;
	int	valid;

	i = 0;
	valid = 0;
	parse->cmdstr = NULL;
	while (str[i])
	{
		if (ft_isalnum(str[i]))
			valid = 1;
		else if (!ft_isascii(str[i]))
		{
			valid = 0;
			break ;
		}
		i++;
	}
	if (!valid)
	{
		free(str);
		ft_perror("ERROR", NULL, "Invalid input found.");
		parse->status = SYNTAX_ERROR;
		return ;
	}
	parse->cmdstr = str;
}

//Allocates memory for t_cmd object and initialises members.
void	_init_cmd(t_parse *parse)
{
	parse->cmd->delimiter = NULL;
	parse->cmd->infile = NULL;
	parse->cmd->outfile = NULL;
	parse->cmd->output_flag = 'w';
	parse->cmd->cmd_table = NULL;
	parse->cmd->pipecount = 0;
	parse->cmd->status = 0;
}

//De-allocates members of t_cmd object, passed as void*
void	_delete_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = content;
	ft_free_strarr(cmd->cmd_table);
	free(cmd->delimiter);
	free(cmd->infile);
	free(cmd->outfile);
}
