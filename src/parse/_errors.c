/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _errors.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/09 13:06:05 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/13 16:32:29 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Encountered parsing error, terminates program with given exit code.
void	_terminate(t_list **cmdlist, t_parse *parse, char *message, int status)
{
	_free_parse(parse);
	ft_lstclear(cmdlist, delete_cmd);
	ft_errexit(message, status);
}
