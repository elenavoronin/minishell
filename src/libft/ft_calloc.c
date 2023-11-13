/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 14:37:07 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/13 17:29:45 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!count || !size)
		return (NULL);
	ptr = ft_malloc_wrapper(count * size);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}

void	*ft_malloc_wrapper(size_t size)
{
	void	*alloc;

	alloc = malloc(size);
	if (!alloc)
		ft_putendl_fd("CRITICAL ERROR: malloc failure!", STDERR_FILENO);
	return (alloc);
}
