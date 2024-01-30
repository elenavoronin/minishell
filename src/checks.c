/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/30 16:20:50 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export_check_cmds(char **cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds && cmds[i])
	{
		if (!ft_isalpha(cmds[i][0]) && cmds[i][0] != '_')
		{
			ft_perror("🐢shell: export", cmds[i], "not a valid identifier");
			return (SYNTAX_ERROR);
		}
		else
		{
			j = 0;
			while (cmds[i][j] && cmds[i][j] != '=')
			{
				if (!ft_isalnum(cmds[i][j]) && cmds[i][j] != '_')
				{
					ft_perror("🐢shell: export", cmds[i], "not a valid identifier");
					return (SYNTAX_ERROR);
				}
				j++;
			}
		}
		i++;
	}
	return (SUCCESS);
}

int	minishell_check_line(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_isspace(line[i]))
			return (SUCCESS);
		i++;
	}
	return (SYNTAX_ERROR);
}
