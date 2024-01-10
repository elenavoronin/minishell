/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enviro.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: elenavoronin <elnvoronin@gmail.com>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/02 13:36:06 by evoronin      #+#    #+#                 */
/*   Updated: 2024/01/10 12:56:11 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRO_H
# define ENVIRO_H

# include "minishell.h"

typedef struct s_env
{
	int		count;
	char	**envp;
	char	**envp_name;
	char	**envp_value;
}	t_env;

typedef struct s_exp
{
	t_env	cmdenv;
	int		ipos;
	char	**cmd;
	char	**newenvp;
}	t_exp;

int		init_env(t_env *env, char **envp);
char	*getenvp_value(t_env *env, char *name);
int		update_envp(t_env *env, char *name, char *value);
void	clear_env(t_env *env);

#endif
