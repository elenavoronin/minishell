/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 15:52:33 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/03 13:12:57 by dliu          ########   odam.nl         */
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

	if (!lst || !*lst || !del)
		return ;
	while (*lst)
	{
		victim = (*lst);
		*lst = (*lst)->next;
		ft_lstdelone(victim, del);
	}
}
