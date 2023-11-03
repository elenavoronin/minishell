/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 14:37:07 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/02 14:11:42 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!count || !size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}
