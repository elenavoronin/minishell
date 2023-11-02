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
#include "libft.h"

t_cmd	*_init_cmd(void);
void	_delete_cmd(void *content);

/**
 * Parses input. Allocates memory.
 * @param input The string to parses.
 * @return On success, returns pointer to head of list, else NULL.
*/
t_list	*parse_input(char *input)
{
	t_list		*head;
	t_cmd		*cmdnode;

	if (!input)
		ft_error("Error: parse_input function needs input.");
	head = NULL;
	cmdnode = NULL;
	// while (*input)
	// {
	// 	cmdnode = _init_cmd();
	// 	//logic goes here
	// 	head = ft_lstnew(cmdnode);
	// 	ft_lstadd_back(&head, ft_lstnew(cmdnode));
	// }
	return (head);
}

/**
 * Frees any allocated memory after procesing an input.
 * Use before processing any more inputs.
*/
void	parse_free(t_list *cmdlist)
{
	ft_lstclear(&cmdlist, _delete_cmd);
}

t_cmd	*_init_cmd(void)
{
	t_cmd	*cmdnode;

	cmdnode = malloc(sizeof(cmdnode));
	if (cmdnode)
	{
		cmdnode->delimiter = NULL;
		cmdnode->input = NULL;
		cmdnode->output = NULL;
		cmdnode->output_flag = 'w';
		cmdnode->cmds = NULL;
		cmdnode->count = 0;
		cmdnode->status = 0;
	}
	return (cmdnode);
}

void	_delete_cmd(void *content)
{
	t_cmd	*cmdnode;

	cmdnode = content;
	ft_free_strarr(cmdnode->cmds);
	free(cmdnode->delimiter);
	free(cmdnode->input);
	free(cmdnode->output);
}
