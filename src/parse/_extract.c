/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _extract.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/14 17:13:58 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_valid_str(char *str);

void	_extract_cmdstr(char *input, t_parse *parse)
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
