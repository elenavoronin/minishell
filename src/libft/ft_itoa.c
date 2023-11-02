/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:21:22 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/01 15:38:57 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument.
 */
char	*ft_itoa(int n)
{
	int				len;
	unsigned int	num;
	char			*buffer;

	len = ft_numlen(n, 10);
	buffer = ft_calloc(len + 1, sizeof (*buffer));
	if (!buffer)
		return (NULL);
	len--;
	if (n == 0)
		buffer[len] = '0';
	num = n;
	if (n < 0)
	{
		buffer[0] = '-';
		num = -n;
	}
	while (num > 0)
	{
		buffer[len] = '0' + (num % 10);
		num = num / 10;
		len--;
	}
	return (buffer);
}
