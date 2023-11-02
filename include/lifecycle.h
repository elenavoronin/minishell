/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lifecycle.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: evoronin <evoronin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:52:05 by evoronin      #+#    #+#                 */
/*   Updated: 2023/11/02 14:52:17 by evoronin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIFECYCLE_H
# define LIFECYCLE_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct s_mini_env
{
    char    *variable_name;
    char    *variable_path;
};


typedef struct s_shell_state
{
    int     status_code;
    char    **mini_env;
}   t_shell_state;


void    start_minishell(int argc, char **argv, char **envp);

#endif