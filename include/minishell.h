/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:36:06 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/14 19:30:03 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700

# ifndef DEBUG
#  define DEBUG 0
# endif

// # include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "enviro.h"
# include "parse.h"
# include "signals.h"
# include "execute.h"
# include "builtins.h"

void	start_minishell(t_shell	*shell);
int		update_status(t_shell *shell, t_status status);
void	delete_cmd(void *content);

#endif
