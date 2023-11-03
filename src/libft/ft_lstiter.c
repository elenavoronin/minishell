/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 17:26:42 by dliu          #+#    #+#                 */
/*   Updated: 2022/10/19 18:16:16 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (f && lst)
	{
		while (lst != NULL)
		{
			f(lst->content);
			lst = lst->next;
		}
	}
}
