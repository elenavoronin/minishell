/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_b.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 17:12:21 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/14 12:19:27 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envp_elements(char **envp)
{
	int	count;

	count = 0;
	while (envp[count] != NULL)
		count++;
	return (count);
}

void	print_env_arr(char **mini_env)
{
	int	i;

	i = 0;
	while (mini_env[i] != NULL)
	{
		printf("[%d]: %s\n", i, mini_env[i]);
		i++;
	}
}
