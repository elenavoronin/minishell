/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _tokenise.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/15 15:47:17 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	_init_cmd(t_shell *shell);
static int	_tokens_to_cmd(char **tokens, t_cmd *cmd, t_shell *shell);
static char	**_get_token_dest(char *token, t_cmd *cmd);
static int	_update_cmdtable(char *token, t_cmd *cmd, t_shell *shell);

int	_tokenise(char	**tokens, t_shell *shell)
{
	t_cmd	*cmd;

	_init_cmd(shell);
	while (*tokens && shell->status == SUCCESS)
	{
		cmd = ft_lstlast(shell->cmdlist)->content;
		if (_tokens_to_cmd(tokens, cmd, shell) != SUCCESS)
			break ;
		tokens++;
		if (ft_strcmp(*tokens, "|") == 0)
		{
			if (_init_cmd(shell) != SUCCESS)
				break ;
			tokens++;
		}
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
	cmd->delimiter = NULL;
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

static int	_tokens_to_cmd(char **tokens, t_cmd *cmd, t_shell *shell)
{
	char	**dest;

	dest = _get_token_dest(*tokens, cmd);
	if (dest && dest != cmd->cmd_table)
	{
		tokens++;
		if (!*tokens)
		{
			ft_perror("🐢shell", "syntax error", "bad command");
			return (update_status(shell, SYNTAX_ERROR));
		}
		if (*dest)
			free(*dest);
		*dest = ft_strdup(*tokens);
		if (!*dest)
			return (update_status(shell, MALLOC_ERROR));
	}
	else
		_update_cmdtable(*tokens, cmd, shell);
	return (SUCCESS);
}

static char	**_get_token_dest(char *token, t_cmd *cmd)
{
	char	**dest;

	dest = NULL;
	if (ft_strcmp(token, "<<") == 0)
		dest = &(cmd->delimiter);
	else if (ft_strcmp(token, "<") == 0)
		dest = &(cmd->infile);
	else if (ft_strcmp(token, ">") == 0)
		dest = &(cmd->outfile);
	else if (ft_strcmp(token, ">>") == 0)
	{
		cmd->output_flag = 'a';
		dest = &(cmd->outfile);
	}
	else if (*token)
	{
		cmd->cmd_argc++;
		dest = cmd->cmd_table;
	}
	return (dest);
}

static int	_update_cmdtable(char *token, t_cmd *cmd, t_shell *shell)
{
	char	**cmdtable;
	size_t	i;

	cmdtable = ft_calloc((cmd->cmd_argc + 1), sizeof(*cmdtable));
	if (!cmdtable)
		return (update_status(shell, MALLOC_ERROR));
	i = 0;
	while (i < cmd->cmd_argc)
	{
		if (cmd->cmd_table && cmd->cmd_table[i])
			cmdtable[i] = ft_strdup(cmd->cmd_table[i]);
		else
			cmdtable[i] = ft_strdup(token);
		if (!cmdtable[i])
			break ;
		i++;
	}
	cmdtable[i] = NULL;
	ft_free_strarr(cmd->cmd_table);
	cmd->cmd_table = cmdtable;
	if (i < cmd->cmd_argc)
		return (update_status(shell, MALLOC_ERROR));
	return (SUCCESS);
}
