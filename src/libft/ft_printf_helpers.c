/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_helpers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 16:17:12 by dliu          #+#    #+#                 */
/*   Updated: 2022/12/13 14:36:23 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	add_node(t_print *tab, char *content, const int addback)
{
	t_list	*node;

	node = NULL;
	if (content)
		node = ft_lstnew(content);
	if (!node || !content)
	{
		free(content);
		tab->count = -1;
		return (0);
	}
	else if (addback)
		ft_lstadd_back(&tab->plist, node);
	else
		ft_lstadd_front(&tab->plist, node);
	return (1);
}

void	check_write(t_print *tab)
{
	int			check;
	t_list		*pnode;
	char		*content;

	check = tab->count;
	pnode = tab->plist;
	while (pnode != NULL && tab->count > -1)
	{
		content = pnode->content;
		if (content && content[0])
			tab->count += write(1, pnode->content, ft_strlen(pnode->content));
		else if (!tab->iszero)
			tab->count += write(1, "\0", 1);
		if (tab->count < check)
			tab->count = -1;
		pnode = pnode->next;
	}
}
