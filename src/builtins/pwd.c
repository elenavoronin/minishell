/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:47:55 by dliu          #+#    #+#                 */
/*   Updated: 2023/12/12 14:01:19 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_pwd(void)
{
	char	*buffer;

	buffer = NULL;
	getcwd(buffer, 0);
	if (!buffer)
		write(STDERR_FILENO, "ERROR", 5);
	write(STDOUT_FILENO, buffer, ft_strlen(buffer));
	write(STDOUT_FILENO, "\n", 1);
	free(buffer);
}
