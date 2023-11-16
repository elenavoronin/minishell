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

static void	_init_parse(t_parse *parse, t_list **cmdlist, t_shell_state *shell_state);
static void	_extract_cmdstr(char *input, t_parse *parse);
static int	_valid_str(char *str);

/**
 * Parses input. Allocates memory.
 * @param input The string to parses.
 * @return On success, returns pointer to head of list.
 * Will terminate program with appropriate exit code on failure.
*/
t_list	*parse_input(char *input, t_shell_state	*shell_state)
{
	t_list	*cmdlist;
	t_parse	parse;

	if (!input)
		_terminate(NULL, "ERROR: Parser input NULL.", INTERNAL_ERROR);
	cmdlist = NULL;
	while (*input)
	{
		_init_parse(&parse, &cmdlist, shell_state);
		_extract_cmdstr(input, &parse);
		if (parse.status != SUCCESS)
			_terminate(&cmdlist, NULL, parse.status);
		_tokens_to_cmd(&parse);
		free(parse.cmdstr);
		if (parse.status != SUCCESS)
			_terminate(&cmdlist, NULL, parse.status);
		input += parse.pos;
		if (*input == '|')
			input++;
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

static void	_init_parse(t_parse *parse, t_list **cmdlist, t_shell_state *shell_state)
{
	t_list	*new;

	parse->status = SUCCESS;
	parse->cmdstr = NULL;
	parse->tokens = NULL;
	parse->pos = 0;
	parse->argc = 0;
	parse->cmd = ft_malloc_wrapper(sizeof(*(parse->cmd)));
	if (!parse->cmd)
		_terminate(cmdlist, NULL, MALLOC_ERROR);
	parse->cmd->delimiter = NULL;
	parse->cmd->infile = NULL;
	parse->cmd->outfile = NULL;
	parse->cmd->output_flag = 'w';
	parse->cmd->cmd_table = NULL;
	new = ft_lstnew(parse->cmd);
	if (!new)
	{
		delete_cmd(parse->cmd);
		_terminate(NULL, NULL, MALLOC_ERROR);
	}
	ft_lstadd_back(cmdlist, new);
	parse->shell_state = shell_state;
}

static void _extract_cmdstr(char *input, t_parse *parse)
{
	char	*str;
	char	*end;

	end = ft_strchr(input, '|');
	if (end)
		parse->pos = end - 1 - input;
	else
		parse->pos = ft_strlen(input);
	str = ft_substr(input, 0, parse->pos);
	if (!str)
	{
		parse->status = MALLOC_ERROR;
		return ;
	}
	if (!_valid_str(str))
	{
		free(str);
		parse->status = SYNTAX_ERROR;
		return ;
	}
	parse->cmdstr = str;
}

static int	_valid_str(char *str)
{
	int	i;
	int	valid;

	i = 0;
	valid = 0;
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
		ft_perror("SYNTAX ERROR:", NULL, "Invalid input found.");
	return (valid);
}
