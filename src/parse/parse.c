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

void	_delete_cmd(void *content);

/**
 * Parses input. Allocates memory.
 * @param input The string to parses.
 * @return On success, returns pointer to head of list, else NULL.
*/
t_list	*parse_input(char *input)
{
	t_list	*cmdlist;
	t_parse	parse;

	cmdlist = NULL;
	if (!input)
		_terminate(&cmdlist, "ERROR: parse_input needs input.", MALLOC_ERROR);
	while (*input)
	{
		_extract_cmdstr(input, &parse);
		if (!parse.cmdstr)
			_terminate(&cmdlist, NULL, parse.status);
		parse.cmd = _extract_cmd(parse.cmdstr);
		if (!parse.cmd)
			_terminate(&cmdlist, "ERROR: malloc failure.", MALLOC_ERROR);
		parse.cmdnode = ft_lstnew(parse.cmd);
		if (!parse.cmdnode)
			_terminate(&cmdlist, "ERROR: malloc failure.", MALLOC_ERROR);
		ft_lstadd_back(&cmdlist, parse.cmdnode);
		free(parse.cmdstr);
		input += parse.pos;
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

/**
 * For early terminating if error is encountered during parsing.
 * Frees list, prints message and exits with EXIT_FAILURE
 */
void	_terminate(t_list **cmdlist, char *message, int status)
{
	ft_lstclear(cmdlist, _delete_cmd);
	ft_errexit(message, status);
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
