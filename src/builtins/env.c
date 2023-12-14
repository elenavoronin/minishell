/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/12 17:38:24 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_env(t_env env)
{
	size_t	i;

	i = 0;
	while (env.envp[i])
	{
		ft_putendl_fd(env.envp[i], STDOUT_FILENO);
		i++;
	}
}
