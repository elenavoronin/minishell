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

static void		_init(t_parse *parse, t_shell *shell);
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
		_init(&parse, shell);
		line += _extract_cmdstr(line, &parse);
		if (shell->status != SUCCESS)
			mini_exit(shell);
		_parse_tokens(&parse);
		if (shell->status != SUCCESS)
			mini_exit(shell);
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

	cmd = content;
	ft_free_strarr(cmd->cmd_table);
	free(cmd->delimiter);
	free(cmd->infile);
	free(cmd->outfile);
	free(cmd);
}

static void	_init(t_parse *parse, t_shell *shell)
{
	t_list	*new;

	parse->shell = shell;
	parse->cmdstr = NULL;
	parse->argc = 0;
	parse->cmd = ft_malloc_wrapper(sizeof(*(parse->cmd)));
	if (!parse->cmd)
		mini_exit(shell);
	parse->cmd->delimiter = NULL;
	parse->cmd->infile = NULL;
	parse->cmd->outfile = NULL;
	parse->cmd->output_flag = 'w';
	parse->cmd->cmd_table = NULL;
	new = ft_lstnew(parse->cmd);
	if (!new)
	{
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
		return (update_status(parse->shell, MALLOC_ERROR), 0);
	parse->cmdstr = str;
	return (len);
}
