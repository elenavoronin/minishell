/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 12:58:24 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/29 15:16:57 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	mini_env(t_env env, int fd)
{
	int	i;

	i = 0;
	while (i < env.count)
	{
		if (env.envp_value[i])
			ft_putendl_fd(env.envp[i], fd);
		i++;
	}
}
