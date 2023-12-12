/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/21 17:21:49 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/12 13:58:06 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		check_builtins(char **cmd);
void	execute_builtins(char **cmd, t_shell_state *state);
void	mini_env(char **envp);
void	mini_echo(char **cmd);
void	mini_pwd(void);
void	mini_exit(t_shell_state *state);

#endif
