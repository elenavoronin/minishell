/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ltoa_unsigned_base.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 12:21:22 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/13 17:24:02 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ltoa_extend(unsigned long num, char *buffer, int len, int base);

/**
 * Allocates (with malloc(3)) and returns a string
 * representing the unsigned number received as an argument.
 * Negative numbers will not be handled.
 */
char	*ft_ltoa_unsigned_base(unsigned long num, int base)
{
	char			*buffer;
	int				len;
	unsigned long	tmp;

	if (num == 0)
		len = 1;
	else
	{
		len = 0;
		tmp = num;
		while (tmp > 0)
		{
			tmp = tmp / base;
			len++;
		}
	}
	buffer = ft_calloc(len + 1, sizeof(*buffer));
	if (!buffer)
		return (NULL);
	buffer[len] = '\0';
	len--;
	ltoa_extend(num, buffer, len, base);
	return (buffer);
}

static void	ltoa_extend(unsigned long num, char *buffer, int len, int base)
{
	int	rem;

	rem = 0;
	while (len >= 0)
	{
		rem = num % base;
		if (rem >= 10)
			buffer[len] = 'a' + (rem - 10);
		else
			buffer[len] = '0' + rem;
		num = num / base;
		len--;
	}
}
