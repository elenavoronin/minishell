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

static int		_init_parse(t_parse *parse, t_shell *shell);
static void		_clear_cmdstr(t_parse *parse);

/**
 * Parses shell->line. Allocates memory for linked list and content.
 * @return On success, returns pointer to head of list.
*/
void	parse_input(t_shell *shell)
{
	t_parse	parse;

	parse.line = shell->line;
	while (parse.line)
	{
		if (_init_parse(&parse, shell) != SUCCESS)
			return (_clear_parse(&parse));
		if (_extract(&parse, shell) != SUCCESS)
			return (_clear_parse(&parse));
		if (_split(&parse) != SUCCESS)
			return (_clear_parse(&parse));
		if (_tokenise(&parse) != SUCCESS)
			return (_clear_parse(&parse));
		if (*parse.line == '|')
			parse.line++;
	}
	_clear_parse(&parse);
}

static int	_init_parse(t_parse *parse, t_shell *shell)
{
	t_list	*new;

	parse->cmdend = ft_strchr(parse->line, '|');
	if (!parse->cmdend)
		parse->cmdend = ft_strchr(parse->line, '\0');
	parse->cmd = ft_calloc(1, sizeof(*parse->cmd));
	if (!parse->cmd)
		return (update_status(shell, MALLOC_ERROR));
	parse->cmd->delimiter = NULL;
	parse->cmd->infile = NULL;
	parse->cmd->outfile = NULL;
	parse->cmd->output_flag = 'w';
	parse->cmd->cmd_table = NULL;
	parse->cmd->cmd_argc = 0;
	new = ft_lstnew(parse->cmd);
	if (!new)
	{
		free(parse->cmd);
		return (update_status(shell, MALLOC_ERROR));
	}
	ft_lstadd_back(&shell->cmdlist, new);
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
