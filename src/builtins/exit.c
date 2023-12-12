/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/12 13:30:16 by dliu          #+#    #+#                 */
/*   Updated: 2023/12/12 13:44:07 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//needs to exit before forking if this is the first command
void	mini_exit(t_shell_state *state)
{
	clear_shell_state(state);
	exit(EXIT_SUCCESS);
}
