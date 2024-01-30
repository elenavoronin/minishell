/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_check.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/30 15:03:25 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	export_check_cmds(char **cmds)
{
	int	i;

	i = 0;
	while (cmds && cmds[i])
	{
		if (ft_isalpha(cmds[i][0]) == 0 && cmds[i][0] != '_')
		{
			ft_perror("🐢shell: export", cmds[i], "not a valid identifier");
			return (SYNTAX_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
