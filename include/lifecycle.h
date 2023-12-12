/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:52:05 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/12 17:17:14 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFECYCLE_H
# define LIFECYCLE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

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

typedef struct s_env
{
	char	**envp;
	char	**envp_name;
	char	**envp_value;
}	t_env;

typedef struct s_shell
{
	t_status	status;
	t_env		env;
	int			return_value;
}	t_shell;

void	start_minishell(int argc, char **argv, char **envp);
char	*getenvp_value(t_shell *shell, char *name);
void	update_envp(t_shell *shell, char *name, char *value);
void	update_status(t_shell *shell, t_status status);

#endif
