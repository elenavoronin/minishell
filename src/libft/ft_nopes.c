/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nopes.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 16:57:09 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/01 15:21:37 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Prints an error message and exits with exit code EXIT_FAILURE.
 * NULL inputs will be skipped.
*/
void	ft_error(char *errmsg)
{
	if (errmsg)
		ft_putendl_fd(errmsg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

/**
 * Prints an error message based on inputs. 
 * NULL inputs will be skipped.
*/
void	ft_perror(char *progname, char *funcname, char *messsage)
{
	if (progname)
	{
		ft_putstr_fd(progname, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (funcname)
	{
		ft_putstr_fd(funcname, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (messsage)
		ft_putendl_fd(messsage, STDERR_FILENO);
}
