/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _tokenise.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/31 15:10:44 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	_init_cmd(t_shell *shell);
static int	_tokens_to_cmd(t_tok *tok, t_shell *shell);
static void	_get_token_dest(t_tok *tok);
static int	_update_cmdtable(t_tok *tok, t_shell *shell);

int	_tokenise(char	**tokens, t_shell *shell)
{
	t_tok	tok;

	_init_cmd(shell);
	tok.tokens = tokens;
	while (*tok.tokens && shell->status == SUCCESS)
	{
		tok.cmd = ft_lstlast(shell->cmdlist)->content;
		if (_tokens_to_cmd(&tok, shell) != SUCCESS)
			break ;
		tok.tokens++;
		if (*tok.tokens && *tok.tokens[0] == '|')
		{
			if (_init_cmd(shell) != SUCCESS)
				break ;
			if (ft_strlen(*tok.tokens) == 1)
				tok.tokens++;
			if (!*tok.tokens || (*tok.tokens && !*tok.tokens[0]))
			{
				ft_perror("🐢shell", "syntax error", "bad command");
				return (update_status(shell, SYNTAX_ERROR));
			}
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

static int	_tokens_to_cmd(t_tok *tok, t_shell *shell)
{
	_get_token_dest(tok);
	if (tok->dest && tok->dest != tok->cmd->cmd_table)
	{
		tok->tokens++;
		if (parse_check_tokens(*tok->tokens) != SUCCESS)
		{
			ft_perror("🐢shell", "syntax error", "bad command");
			return (update_status(shell, SYNTAX_ERROR));
		}
		if (*tok->dest)
			free(*tok->dest);
		*tok->dest = ft_strdup(*tok->tokens);
		if (!*tok->dest)
			return (update_status(shell, MALLOC_ERROR));
	}
	else
		_update_cmdtable(tok, shell);
	return (SUCCESS);
}

static void	_get_token_dest(t_tok *tok)
{
	tok->dest = NULL;
	if (!tok->tokens)
		return ;
	if (ft_strcmp(*tok->tokens, "<<") == 0)
		tok->dest = &(tok->cmd->delimiter);
	else if (ft_strcmp(*tok->tokens, "<") == 0)
		tok->dest = &(tok->cmd->infile);
	else if (ft_strcmp(*tok->tokens, ">") == 0)
		tok->dest = &(tok->cmd->outfile);
	else if (ft_strcmp(*tok->tokens, ">>") == 0)
	{
		tok->cmd->output_flag = 'a';
		tok->dest = &(tok->cmd->outfile);
	}
	else
		tok->dest = tok->cmd->cmd_table;
}

static int	_update_cmdtable(t_tok *tok, t_shell *shell)
{
	char	**newtable;
	size_t	i;

	newtable = ft_calloc((tok->cmd->cmd_argc + 2), sizeof(*newtable));
	if (!newtable)
		return (update_status(shell, MALLOC_ERROR));
	i = 0;
	while (i < tok->cmd->cmd_argc && shell->status == SUCCESS)
	{
		newtable[i] = ft_strdup(tok->cmd->cmd_table[i]);
		if (!newtable[i])
			update_status(shell, MALLOC_ERROR);
		i++;
	}
	if (shell->status == SUCCESS)
		newtable[i] = ft_strdup(*tok->tokens);
	if (!newtable[i])
	{
		ft_free_strarr(newtable);
		return (update_status(shell, MALLOC_ERROR));
	}
	tok->cmd->cmd_argc++;
	ft_free_strarr(tok->cmd->cmd_table);
	tok->cmd->cmd_table = newtable;
	return (shell->status);
}
