/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strhelpers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/05 18:22:25 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/19 13:19:47 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

//Counts continuous recurrances of c
size_t	ft_charcount(char *str, char c)
{
	size_t	len;

	len = 0;
	while (str[len] && str[len] == c)
	{
		len++;
	}
	return (len);
}

//Counts and returns the amount of strings in a NULL terminated string array.
size_t	ft_strarray_count(char **s)
{
	size_t	count;

	count = 0;
	while (s && s[count])
		count++;
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;

	if (src == NULL && dstsize > 0)
	{
		*dst = '\0';
		return (0);
	}
	srclen = ft_strlen(src);
	if (dstsize > srclen)
		ft_memcpy(dst, src, srclen + 1);
	else if (dstsize > 0)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = '\0';
	}
	return (srclen);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			i;
	const size_t	dstlen = ft_strlen(dst);
	const size_t	srclen = ft_strlen(src);

	if (dstlen >= dstsize || dstsize == 0)
		return (dstsize + srclen);
	i = 0;
	while (src[i] != '\0' && i < dstsize - dstlen - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
