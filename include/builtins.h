/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:49 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/24 13:38:29 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	check_builtins(char **cmd, t_pipes_struct *pipes);
void    ft_env(char **cmd, const t_shell_state shell_state);

#endif
