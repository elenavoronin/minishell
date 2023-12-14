/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:47:55 by dliu          #+#    #+#                 */
/*   Updated: 2023/12/12 17:17:35 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_pwd(t_shell *shell)
{
	ft_putendl_fd(getenvp_value(shell, "PWD"), STDOUT_FILENO);
}
