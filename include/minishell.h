/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:36:06 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/12 11:23:27 by elenavoroni   ########   odam.nl         */
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
# include "signals.h"
# include "parse.h"
# include "execute.h"
# include "builtins.h"

void	update_status(t_shell *shell, t_status status);

#endif
