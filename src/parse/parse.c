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

static void		_init(t_parse *parse, t_list **cmdlist, t_shell *shell);
static size_t	_extract_cmdstr(char *input, t_parse *parse);
static int		_valid_str(char *str);

/**
 * Parses input. Allocates memory.
 * @param input The string to parses.
 * @return On success, returns pointer to head of list.
 * Will terminate program with appropriate exit code on failure.
*/
t_list	*parse_input(char *input, t_shell	*shell)
{
	t_list	*cmdlist;
	t_parse	parse;

	if (!input)
		_terminate(NULL, "ERROR: Parser input NULL.", INTERNAL_ERROR);
	cmdlist = NULL;
	while (*input)
	{
		_init(&parse, &cmdlist, shell);
		input += _extract_cmdstr(input, &parse);
		if (parse.shell->status != SUCCESS)
			_terminate(&cmdlist, NULL, parse.shell->status);
		_parse_tokens(&parse);
		if (parse.shell->status != SUCCESS)
			_terminate(&cmdlist, NULL, parse.shell->status);
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

static void	_init(t_parse *parse, t_list **cmdlist, t_shell *shell)
{
	t_list	*new;

	parse->shell = shell;
	parse->shell->status = 0;
	parse->cmdstr = NULL;
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
	if (!_valid_str(str))
	{
		free(str);
		return (update_status(parse->shell, SYNTAX_ERROR), 0);
	}
	parse->cmdstr = str;
	return (len);
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
