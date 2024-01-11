/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 12:58:24 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/10 12:51:03 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	mini_env(t_env env)
{
	int	i;

	i = 0;
	while (i < env.count)
	{
		if (env.envp_value[i])
			ft_putendl_fd(env.envp[i], STDOUT_FILENO);
		i++;
	}
}
