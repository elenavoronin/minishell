/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _extract.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/01 16:10:26 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/09 19:40:02 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_validate_str(char *str, t_parse *parse);

void	_extract_cmdstr(char *input, t_parse *parse)
{
	char	*str;
	size_t	start;

	while (ft_isspace(input[parse->pos]))
		parse->pos++;
	start = parse->pos;
	while (input[parse->pos] && input[parse->pos] != '|')
		parse->pos++;
	if (input[parse->pos] == '|')
		str = ft_substr(input, start, parse->pos - 1);
	else
		str = ft_substr(input, start, parse->pos);
	if (!str)
	{
		_malloc_error(parse);
		parse->cmdstr = NULL;
		return ;
	}
	_validate_str(str, parse);
}

static void	_validate_str(char *str, t_parse *parse)
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
	{
		free(str);
		ft_perror("ERROR", NULL, "Invalid input found.");
		parse->status = SYNTAX_ERROR;
		parse->cmdstr = NULL;
		return ;
	}
	parse->cmdstr = str;
}
