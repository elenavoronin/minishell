/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:52:05 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/20 19:39:25 by codespace     ########   odam.nl         */
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

typedef struct s_shell_state
{
	t_status	status;
	t_env		env;
}	t_shell_state;

void	start_minishell(int argc, char **argv, char **envp);
void	print_env(const t_shell_state shell_state);
char	*getenvp_value(t_shell_state *shell_state, char *name);
void	print_env_test(const t_shell_state shell_state);
void	update_status(t_shell_state *shell_state, t_status status);

#endif
