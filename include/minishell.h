/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:36:06 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/04 11:53:52 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "enviro.h"
# include "signals.h"
# include <linux/limits.h>

typedef enum e_status
{
	SUCCESS,
	MALLOC_ERROR,
	SYNTAX_ERROR,
	UNSUPPORTED,
	PIPE_ERROR,
	INTERNAL_ERROR,
	REDIRECT_ERROR,
	FORK_ERROR,
}	t_status;

typedef struct s_shell
{
	int			run;
	t_status	status;
	t_env		env;
	char		*line;
	t_list		*cmdlist;
	int			return_value;
}	t_shell;

# include "parse.h"
# include "execute.h"
# include "builtins.h"
# include <readline/readline.h>
# include <readline/history.h>

void	update_status(t_shell *shell, t_status status);

#endif
