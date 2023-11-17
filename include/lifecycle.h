/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:52:05 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/17 15:42:34 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFECYCLE_H
# define LIFECYCLE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef enum e_status_code
{
	SUCCESS,
	MALLOC_ERROR,
	SYNTAX_ERROR,
	UNSUPPORTED,
	PIPE_ERROR,
	INTERNAL_ERROR,
	REDIRECT_ERROR,
	FORK_ERROR,
}	t_status_code;

typedef struct s_mini_env
{
	char	*variable_name;
	char	*variable_path;
}	t_mini_env;

typedef struct s_shell_state
{
	t_status_code	status_code;
	t_mini_env		*mini_env;
	char			**env_path_arr;
}	t_shell_state;

void	start_minishell(int argc, char **argv, char **envp);
int		env_path_arr(t_shell_state *shell_state, char **envp);
void	init_shell_state(t_shell_state *shell_state, char **envp);
void	clear_shell_state(t_shell_state *shell_state);
void	print_env_arr(char **env_path_arr);
int		count_envp_elements(char **envp);
void	update_status_code(t_shell_state *shell_state, t_status_code status);
int		count_envp_elements(char **envp);
int		env_path_arr_for_printing(t_shell_state *shell_state, char **envp);

#endif
