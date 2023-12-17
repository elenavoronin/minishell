/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enviro.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:36:06 by evoronin      #+#    #+#                 */
/*   Updated: 2023/12/17 16:31:28 by codespace     ########   odam.nl         */
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
	t_status	status;
	t_env		env;
	char		*line;
	t_list		*cmdlist;
	int			return_value;
}	t_shell;

void	init_env(t_shell *shell, char **envp);
char	*getenvp_value(t_shell *shell, char *name);
void	update_envp(t_shell *shell, char *name, char *value);
void	clear_env(t_shell *shell);
void	update_status(t_shell *shell, t_status status);

#endif
