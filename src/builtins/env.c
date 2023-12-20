/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/15 12:58:24 by codespace     #+#    #+#                 */
/*   Updated: 2023/12/19 09:59:41 by elenavoroni   ########   odam.nl         */
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
