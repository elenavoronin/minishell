/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:47:55 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/29 15:41:21 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	mini_pwd(t_shell *shell, int outfile)
{
	ft_putendl_fd(getenv_value(shell->env, "PWD"), outfile);
}
