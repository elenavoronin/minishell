/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _copy.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:48:52 by dliu          #+#    #+#                 */
/*   Updated: 2024/02/01 21:14:52 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_copy_tmp(t_shell *shell, t_parse *parse)
{
	char	*substr;

	if (parse->pos <= parse->str)
		return (SUCCESS);
	substr = ft_substr(parse->str, 0, parse->pos - parse->str);
	if (!substr)
		return (update_status(shell, MALLOC_ERROR));
	parse->tmp = ft_strcat_free(parse->tmp, substr);
	if (!parse->tmp)
		return (update_status(shell, MALLOC_ERROR));
	parse->str = parse->pos;
	return (SUCCESS);
}

int	_copy_str(t_shell *shell, t_parse *parse, char *str)
{
	parse->tmp = ft_strcat_free(parse->tmp, str);
	if (!parse->tmp)
		return (update_status(shell, MALLOC_ERROR));
	return (SUCCESS);
}

int	_copy_fin(t_shell *shell, t_parse *parse)
{
	if (_copy_tmp(shell, parse) != SUCCESS)
		return (shell->status);
	if (parse->tmp)
	{
		parse->result[parse->i] = parse->tmp;
		parse->tmp = NULL;
		parse->i++;
	}
	return (SUCCESS);
}
