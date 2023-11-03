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

t_cmd	*_init_cmd(void);
void	_delete_cmd(void *content);

/**
 * Parses input. Allocates memory.
 * @param input The string to parses.
 * @return On success, returns pointer to head of list, else NULL.
*/
t_list	*parse_input(char *input)
{
	t_list	*cmdlist;
	t_list	*cmdnode;
	t_cmd	*cmd;
	size_t	pos;

	cmdlist = NULL;
	if (!input)
		_parse_terminate(&cmdlist, "ERROR: parse_input function needs input.");
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		cmd = _init_cmd();
		pos = _extract_cmd(input, &pos);
		if (!cmd)
			_parse_terminate(&cmdlist, "ERROR: malloc failure.");
		cmdnode = ft_lstnew(cmd);
		if (!cmdnode)
			_parse_terminate(&cmdlist, "ERROR: malloc failure.");
		ft_lstadd_back(&cmdlist, cmdnode);
		input += pos;
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
void	_terminate_parsing(t_list **cmdlist, char *message)
{
	ft_lstclear(cmdlist, _delete_cmd);
	ft_error(message);
}

//Allocates memory for t_cmd object and initialises members.
t_cmd	*_init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(cmd));
	if (cmd)
	{
		cmd->delimiter = NULL;
		cmd->input = NULL;
		cmd->output = NULL;
		cmd->output_flag = 'w';
		cmd->cmd_table = NULL;
		cmd->status = 0;
	}
	return (cmd);
}

//De-allocates members of t_cmd object, passed as void*
void	_delete_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = content;
	ft_free_strarr(cmd->cmd_table);
	free(cmd->delimiter);
	free(cmd->input);
	free(cmd->output);
}
