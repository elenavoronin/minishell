/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_a.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 13:23:27 by elenavoroni   #+#    #+#                 */
/*   Updated: 2023/11/27 15:56:14 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_builtins(char **cmd, t_pipes_struct *pipes)
{
	if (ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "exit") == 0
		|| ft_strcmp(cmd[0], "unset") == 0
		|| ft_strcmp(cmd[0], "export") == 0
		// || ft_strcmp(cmd[0], "echo") == 0
		|| ft_strcmp(cmd[0], "cd") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0)
	{
		pipes->path = ft_strjoin("~/Documents/minishell_daoyi/src/builtins/", cmd[0]);
		return (0);
	}
	return (1);
}
