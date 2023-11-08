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

void	_init_parse(t_parse *parse, t_list **cmdlist);
void	_free_parse(t_parse *parse);

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
		_extract_cmd(&parse);
		if (parse.status)
			_terminate(&cmdlist, &parse, NULL, parse.status);
		input += parse.pos;
		_free_parse(&parse);
	}
	return (cmdlist);
}

/**
 * Frees any allocated memory after procesing an input.
 * Use before processing any more inputs.
*/
void	parse_free(t_list **cmdlist)
{
	ft_lstclear(cmdlist, _delete_cmd);
}

void	_init_parse(t_parse *parse, t_list **cmdlist)
{
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
	if (!*cmdlist)
		*cmdlist = ft_lstnew(parse->cmd);
	else
		ft_lstadd_back(cmdlist, parse->cmd);
}

void	_free_parse(t_parse *parse)
{
	free(parse->cmdstr);
	parse->cmdstr = NULL;
	ft_free_strarr(parse->tokens);
	parse->tokens = NULL;
}

void	_terminate(t_list **cmdlist, t_parse *parse, char *message, int status)
{
	_free_parse(parse);
	ft_lstclear(cmdlist, _delete_cmd);
	ft_errexit(message, status);
}
