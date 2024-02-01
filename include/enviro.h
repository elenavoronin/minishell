/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enviro.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:36:06 by evoronin      #+#    #+#                 */
/*   Updated: 2024/02/01 10:39:55 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRO_H
# define ENVIRO_H

# include "minishell.h"

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
	FAILED
}	t_status;

typedef struct s_env
{
	int		count;
	char	**envp;
	char	**envp_name;
	char	**envp_value;
}	t_env;

typedef struct s_shell
{
	int				run;
	t_status		status;
	t_env			env;
	char			*line;
	t_list			*cmdlist;
	unsigned char	return_value;
}	t_shell;

int		init_env(t_env *env, char **envp);
char	*getenv_value(t_env env, char *name);
int		update_envp(t_env *env, char *name, char *value, int i);
void	clear_env(t_env *env);

#endif
