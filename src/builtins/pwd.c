/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:47:55 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/29 16:48:37 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	mini_pwd(t_shell *shell, int outfile)
{
	ft_putendl_fd(getenv_value(shell->env, "PWD"), outfile);
}
