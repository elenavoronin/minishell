/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:31 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/27 15:58:43 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env(char **cmd, const t_shell_state shell_state)
{
    if (ft_strncmp("env", cmd[0], 4) == 0)
        print_env(shell_state);
}
