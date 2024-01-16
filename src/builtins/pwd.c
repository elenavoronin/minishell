/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:47:55 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/16 13:18:06 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	mini_pwd(t_shell *shell)
{
	ft_putendl_fd(getenv_value(shell->env, "PWD"), STDOUT_FILENO);
}
