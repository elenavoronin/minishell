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

#include "minishell.h"

static void	_init_cmd(t_parse *parse);
static void	_init_parse(t_parse *parse, t_list **cmdlist);

/**
 * Parses input. Allocates memory.
 * @param input The string to parses.
 * @return On success, returns pointer to head of list.
 * Will terminate program with appropriate exit code on failure.
*/
t_list	*parse_input(char *input)
{
	t_list	*cmdlist;
	t_parse	parse;

	if (!input)
		_terminate(NULL, NULL, "ERROR: Parser input NULL.", INTERNAL_ERROR);
	cmdlist = NULL;
	while (*input)
	{
		_init_parse(&parse, &cmdlist);
		_extract_cmdstr(input, &parse);
		if (!parse.cmdstr)
			_terminate(&cmdlist, &parse, NULL, parse.status);
		_tokens_to_cmd(&parse);
		if (parse.status)
			_terminate(&cmdlist, &parse, NULL, parse.status);
		input += parse.pos;
		if (*input == '|')
			input++;
		_free_parse(&parse);
	}
	return (cmdlist);
}

/**
 * Use this function in ft_lstclear after processing each line of input,
 * to free linked list content.
 * 
 * ft_lstclear(cmdlist, delete_cmd);
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

static void	_init_parse(t_parse *parse, t_list **cmdlist)
{
	t_list	*new;

	parse->status = 0;
	parse->cmdstr = NULL;
	parse->tokens = NULL;
	parse->pos = 0;
	parse->count = 0;
	parse->rem = 0;
	parse->cmd = malloc(sizeof(*(parse->cmd)));
	if (!parse->cmd)
		_terminate(cmdlist, parse, "ERROR: Malloc failure", MALLOC_ERROR);
	_init_cmd(parse);
	new = ft_lstnew(parse->cmd);
	if (!new)
	{
		delete_cmd(parse->cmd);
		_terminate(NULL, parse, "ERROR: Malloc failure", MALLOC_ERROR);
	}
	ft_lstadd_back(cmdlist, new);
}

void	_free_parse(t_parse *parse)
{
	free(parse->cmdstr);
	parse->cmdstr = NULL;
	ft_free_strarr(parse->tokens);
	parse->tokens = NULL;
}

static void	_init_cmd(t_parse *parse)
{
	parse->cmd->delimiter = NULL;
	parse->cmd->infile = NULL;
	parse->cmd->outfile = NULL;
	parse->cmd->output_flag = 'w';
	parse->cmd->cmd_table = NULL;
	parse->cmd->status = 0;
}
