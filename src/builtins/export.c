/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/15 16:12:15 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	mini_export(char **cmd, t_shell *shell)
{
	char **sort_envp;
	int	i;

	i = ft_strarray_count(shell->env.envp);
	sort_envp = ft_calloc(i, sizeof(*sort_envp));
	if (!sort_envp)
		return ;
	i = 0;
	while (shell->env.envp[i] && i < shell->env.count)
	{
		if (ft_strcmp(shell->env.envp[i], cmd[1]) == 0)
			shell->env.envp[i] = cmd[1];
		i++;
	}
	
}
