/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle_b.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/07 17:12:21 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/07 17:13:09 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_envp_elements(char **envp) 
{
    int count = 0;

    while (envp[count] != NULL)
        count++;
    return (count);
}

void	print_env_arr(t_mini_env **mini_env)
{
	int	i;

	i = 0;
	while (mini_env[i])
	{
		printf("[%d]: %s\n", i, mini_env[i]->variable_name);
		printf("[%d]: %s\n", i,  mini_env[i]->variable_path);
		i++;
	}
}
