/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 18:19:14 by dliu          #+#    #+#                 */
/*   Updated: 2023/01/25 14:00:23 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*map_node(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mappedlst;
	t_list	*elem;
	t_list	*tail;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	mappedlst = map_node(lst, f, del);
	if (mappedlst != NULL)
	{
		tail = mappedlst;
		lst = lst->next;
		while (lst != NULL)
		{
			elem = map_node(lst, f, del);
			if (elem == NULL)
			{
				ft_lstclear(&mappedlst, del);
				return (NULL);
			}
			tail->next = elem;
			tail = elem;
			lst = lst->next;
		}
	}
	return (mappedlst);
}

static t_list	*map_node(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*ptr;
	t_list	*elem;

	ptr = f(lst->content);
	elem = ft_lstnew(ptr);
	if (elem == NULL)
	{
		del(ptr);
		return (NULL);
	}
	return (elem);
}
