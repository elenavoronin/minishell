/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:37:49 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/10 12:51:18 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	mini_echo(char **cmd)
{
	int	nl;

	nl = 1;
	cmd++;
	if (*cmd && ft_strcmp(*cmd, "-n") == 0)
	{
		nl = 0;
		cmd++;
	}
	while (*cmd)
	{
		write(STDOUT_FILENO, *cmd, ft_strlen(*cmd));
		cmd++;
		if (*cmd)
			write(STDOUT_FILENO, " ", 1);
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
}
