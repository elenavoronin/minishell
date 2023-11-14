/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:52:05 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/14 14:54:33 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFECYCLE_H
# define LIFECYCLE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef enum e_code_status
{
	SUCCESS,
	MALLOC_ERROR,
	SYNTAX_ERROR,
	UNSUPPORTED,
	PIPE_ERROR,
	INTERNAL_ERROR,
	REDIRECT_ERROR,
	FORK_ERROR,
}	t_code_status;

// typedef struct s_mini_env
// {
// 	char	*variable_name;
// 	char	*variable_path;
// }	t_mini_env;

typedef struct s_shell_state
{
	int				status_code;
	char			**mini_env;
}	t_shell_state;


void	start_minishell(int argc, char **argv, char **envp);
int		mini_env_arr(t_shell_state *mini_state, char **envp);
int		init_mini_state(t_shell_state **mini_state, char **envp);
void	clear_mini_env(t_shell_state *mini_state);
void	print_env_arr(char **mini_env);
int		count_envp_elements(char **envp);
void	update_status_code(t_shell_state *mini_state, t_code_status status);
int		count_envp_elements(char **envp);

#endif
