/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:52:33 by dliu          #+#    #+#                 */
/*   Updated: 2022/12/14 15:54:47 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		if (del && lst->content)
			(del(lst->content));
		free(lst);
	}
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*victim;

	if (*lst == NULL || del == NULL)
		return ;
	while (*lst != NULL)
	{
		victim = (*lst);
		*lst = (*lst)->next;
		ft_lstdelone(victim, del);
	}
}
