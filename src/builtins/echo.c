/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 12:37:49 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/29 18:00:06 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_flag(char *str)
{
	size_t	i;

	if (ft_strlen(str) < 2 || (str[0] != '-' || str[1] != 'n'))
		return (0);
	i = 1;
	while (str && str[i])
	{
		if (str[i] == 'n')
			i++;
		else if (str[i] != '\0')
			return (0);
	}
	return (i);
}

int	mini_echo(char **cmd, int fd)
{
	int	nl;

	nl = 1;
	cmd++;
	while (is_flag(*cmd))
		cmd++;
	while (*cmd)
	{
		write(fd, *cmd, ft_strlen(*cmd));
		cmd++;
		if (*cmd)
			write(fd, " ", 1);
	}
	if (nl)
		write(fd, "\n", 1);
	return (SUCCESS);
}
