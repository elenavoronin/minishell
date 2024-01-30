/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:47:55 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/30 14:57:36 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_pwd(t_shell *shell, int outfile)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 0);
	ft_putendl_fd(path, outfile);
	free(path);
	return (SUCCESS);
}
