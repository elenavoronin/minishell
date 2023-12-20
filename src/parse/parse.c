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

static void		_init_parse(t_parse *parse, t_shell *shell);
static t_cmd	*_init_cmd(void);
static size_t	_extract_cmdstr(char *input, t_parse *parse);

/**
 * Parses shell->line. Allocates memory.
 * @return On success, returns pointer to head of list.
 * Will terminate program with appropriate exit code on failure.
*/
void	parse_input(t_shell *shell)
{
	t_parse	parse;
	char	*line;

	line = shell->line;
	while (*line)
	{
		_init_parse(&parse, shell);
		if (shell->status != SUCCESS)
			return ;
		line += _extract_cmdstr(line, &parse);
		if (shell->status != SUCCESS)
			return ;
		_parse_tokens(&parse);
		if (shell->status != SUCCESS)
			return ;
		if (*line == '|')
			line++;
	}
}

/**
 * Use this function in ft_lstclear
*/
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

static t_cmd	*_init_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (cmd)
	{
		cmd->delimiter = NULL;
		cmd->infile = NULL;
		cmd->outfile = NULL;
		cmd->output_flag = 'w';
		cmd->cmd_table = NULL;
	}
	return (cmd);
}

static void	_init_parse(t_parse *parse, t_shell *shell)
{
	t_list	*new;

	new = NULL;
	parse->shell = shell;
	parse->argc = 0;
	parse->cmd = _init_cmd();
	if (parse->cmd)
		new = ft_lstnew(parse->cmd);
	if (!new)
	{
		update_status(shell, MALLOC_ERROR);
		delete_cmd(parse->cmd);
		parse->cmd = NULL;
		mini_exit(shell);
	}
	ft_lstadd_back(&shell->cmdlist, new);
	parse->shell = shell;
}

static size_t	_extract_cmdstr(char *input, t_parse *parse)
{
	size_t	len;
	char	*str;
	char	*end;

	end = ft_strchr(input, '|');
	if (end)
		len = end - input;
	else
		len = ft_strlen(input);
	str = ft_substr(input, 0, len);
	if (!str)
		update_status(parse->shell, MALLOC_ERROR);
	parse->cmdstr = str;
	return (len);
}
