/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_a.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/24 13:23:27 by elenavoroni   #+#    #+#                 */
/*   Updated: 2023/12/11 10:44:45 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_builtins(char **cmd)
{
	if (ft_strcmp(cmd[0], "env") == 0
		|| ft_strcmp(cmd[0], "exit") == 0
		|| ft_strcmp(cmd[0], "unset") == 0
		|| ft_strcmp(cmd[0], "export") == 0
		|| ft_strcmp(cmd[0], "echo") == 0
		|| ft_strcmp(cmd[0], "cd") == 0
		|| ft_strcmp(cmd[0], "pwd") == 0)
		return (1);
	return (0);
}


void	execute_builtins(char **cmd, t_shell_state *state)
{
	if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(state);
}
