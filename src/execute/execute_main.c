/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_main.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 17:00:58 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/08 17:03:33 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    t_dummy_cmd *dummy_cmd;

    int nr = 2;
    dummy_cmd = malloc(sizeof(t_dummy_cmd) * nr);
    if (!dummy_cmd)
        return (-1);
    dummy_cmd->delimiter = NULL;
    
}