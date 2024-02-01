/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _tokenise.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2024/02/01 21:28:26 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	_init_cmd(t_shell *shell);
static int	_update_cmdtable(t_shell *shell, t_parse *parse);
static int	_update_infile(t_shell *shell, t_parse *parse);
static int	_update_outfile(t_shell *shell, t_parse *parse);

static int	_update_infile(t_shell *shell, t_parse *parse)
{
	free(parse->curcmd->infile);
	parse->curcmd->infile = NULL;
	parse->i++;
	if (!parse->result[parse->i])
	{
		write(STDERR_FILENO, "WTF", 4);
		return (update_status(shell, INTERNAL_ERROR));
	}
	if (parse->tokens[parse->i - 1] == IN)
		parse->curcmd->infile = ft_strdup(parse->result[parse->i]);
	else if (parse->tokens[parse->i - 1] == HERE)
	{
		read_heredoc(parse->result[parse->i]);
		parse->curcmd->infile = ft_strdup("temp_heredoc");
		parse->curcmd->tmp = 1;
	}
	if (!parse->curcmd->infile)
		return (update_status(shell, MALLOC_ERROR));
	return (shell->status);
}

static int	_update_outfile(t_shell *shell, t_parse *parse)
{
	free(parse->curcmd->outfile);
	parse->curcmd->outfile = NULL;
	parse->i++;
	if (!parse->result[parse->i])
	{
		write(STDERR_FILENO, "WTF", 4);
		return (update_status(shell, INTERNAL_ERROR));
	}
	parse->curcmd->outfile = ft_strdup(parse->result[parse->i]);
	if (parse->tokens[parse->i - 1] == APPEND)
		parse->curcmd->output_flag = 'a';
	if (!parse->curcmd->outfile)
		return (update_status(shell, MALLOC_ERROR));
	return (shell->status);
}

int	_tokenise(t_shell *shell, t_parse *parse)
{
	_init_cmd(shell);
	parse->i = 0;
	while (parse->result[parse->i] && shell->status == SUCCESS)
	{
		parse->curcmd = ft_lstlast(shell->cmdlist)->content;
		if (parse->tokens[parse->i] == ARG)
			_update_cmdtable(shell, parse);
		else if (parse->tokens[parse->i] == IN
			|| parse->tokens[parse->i] == HERE)
			_update_infile(shell, parse);
		else if (parse->tokens[parse->i] == OUT
			|| parse->tokens[parse->i] == APPEND)
			_update_outfile(shell, parse);
		else if (parse->tokens[parse->i] == PIPE)
		{
			if (_init_cmd(shell) != SUCCESS)
				return (shell->status);
		}
		parse->i++;
	}
	return (shell->status);
}

static int	_init_cmd(t_shell *shell)
{
	t_list	*new;
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	if (!cmd)
		return (update_status(shell, MALLOC_ERROR));
	cmd->cmd_argc = 0;
	cmd->delimiter = 0;
	cmd->tmp = 0;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->output_flag = 'w';
	cmd->cmd_table = NULL;
	cmd->cmd_argc = 0;
	new = ft_lstnew(cmd);
	if (!new)
	{
		free(cmd);
		return (update_status(shell, MALLOC_ERROR));
	}
	ft_lstadd_back(&shell->cmdlist, new);
	return (SUCCESS);
}

static int	_update_cmdtable(t_shell *shell, t_parse *parse)
{
	char	**newtable;
	size_t	i;

	newtable = ft_calloc((parse->curcmd->cmd_argc + 2), sizeof(*newtable));
	if (!newtable)
		return (update_status(shell, MALLOC_ERROR));
	i = 0;
	while (i < parse->curcmd->cmd_argc && shell->status == SUCCESS)
	{
		newtable[i] = ft_strdup(parse->curcmd->cmd_table[i]);
		if (!newtable[i])
			update_status(shell, MALLOC_ERROR);
		i++;
	}
	if (shell->status == SUCCESS)
		newtable[i] = ft_strdup(parse->result[parse->i]);
	if (!newtable[i])
	{
		ft_free_strarr(newtable);
		return (update_status(shell, MALLOC_ERROR));
	}
	parse->curcmd->cmd_argc++;
	ft_free_strarr(parse->curcmd->cmd_table);
	parse->curcmd->cmd_table = newtable;
	return (shell->status);
}
