/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:30:16 by dliu          #+#    #+#                 */
/*   Updated: 2023/12/12 17:17:32 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//needs to exit before forking if this is the only command
void	mini_exit(t_shell *shell)
{
	ft_free_strarr(shell->env.envp_name);
	ft_free_strarr(shell->env.envp_value);
	exit(EXIT_SUCCESS);
}
