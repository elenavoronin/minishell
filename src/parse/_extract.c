/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _extract.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/07 18:55:17 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		_token_type(char *c);
t_cmd	*_init_cmd(void);
int		_validate_str(char *str);

void	_extract_cmdstr(char *input, t_parse *parse)
{
	char	*str;
	int		valid;

	parse->cmdstr = NULL;
	while (ft_isspace(*input))
		input++;
	while (input[parse->pos] && input[parse->pos] != '|')
		parse->pos++;
	str = ft_substr(input, 0, parse->pos);
	if (!str)
	{
		ft_perror("Minishell", NULL, "Likely malloc fail.");
		parse->status = MALLOC_ERROR;
		return ;
	}
	parse->status = _validate_str(str);
	if (parse->status)
	{
		free(str);
		str = NULL;
	}
	parse->cmdstr = str;
}

//WIP HERE
void	_extract_cmd(t_parse *parse)
{
	t_cmd		*cmd;		
	t_tokens	tok;
	char		**split;

	split = ft_split2(parse->cmdstr);
	if (!parse->cmdstr || !split)
		return (NULL);
	tok.pos = 0;
	tok.count = ft_strarray_count(split);
	tok.rem = tok.count;
	while (tok.pos < tok.count)
	{
		tok.pos++;
	}
	cmd = _init_cmd();
	return (cmd);
}

//Allocates memory for t_cmd object and initialises members.
t_cmd	*_init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(cmd));
	if (cmd)
	{
		cmd->delimiter = NULL;
		cmd->infile = NULL;
		cmd->outfile = NULL;
		cmd->output_flag = 'w';
		cmd->cmd_table = NULL;
		cmd->status = 0;
	}
	return (cmd);
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

int	_validate_str(char *str)
{
	int	i;
	int	valid;

	i = 0;
	valid = 0;
	while (str[i])
	{
		if (!ft_isascii(str[i]))
		{
			ft_perror("ERROR", NULL, "Unsupported character found in input.");
			return (UNSUPORTED);
		}
		if (ft_isalnum(str[i]))
			valid = 1;
		i++;
	}
	if (valid)
		return (0);
	return (SYNTAX_ERROR);
}
