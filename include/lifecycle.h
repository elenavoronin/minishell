/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:52:05 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/03 11:58:42 by elenavoroni   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFECYCLE_H
# define LIFECYCLE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct	s_mini_env
{
	char	*variable_name;
	char	*variable_path;
}	t_mini_env;


typedef struct s_shell_state
{
	int		status_code;
	char	**mini_env;
}	t_shell_state;


void	start_minishell(int argc, char **argv, char **envp);

#endif
