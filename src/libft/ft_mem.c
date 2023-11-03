/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mem.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 15:14:45 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/02 14:13:29 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * Locates the first occurance of c in s.
 * @param s Pointer to the first char in a string.
 * @param c The character to find in the string.
 * @param n The maximum amount of bytes to check. 
 * @returns A pointer to the byte located or NULL if not found.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*z;
	unsigned char	ch;

	z = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n > 0)
	{
		if (*z == ch)
			return (z);
		z++;
		n--;
	}
	return (NULL);
}

/**
 * Compares byte string s1 against byte string s2. Both strings are assumed to
 * be n bytes long.
 * @returns The difference between the bytes, treated as unsigned char values.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

/**
 * Copies n bytes from memory area src to memory area dst.
 * Overlap behavior is undefined, use memmove instead.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*cdst;
	const char	*csrc;

	if (!dst || !src)
		return (NULL);
	if (dst != src)
	{
		cdst = (char *)dst;
		csrc = (const char *)src;
		while (n > 0)
		{
			*cdst++ = *csrc++;
			n--;
		}
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*cdst;
	const char	*csrc;

	if (!dst || !src)
		return (NULL);
	if (dst != src)
	{
		cdst = (char *)dst;
		csrc = (const char *)src;
		if (csrc < cdst)
		{
			cdst += len - 1;
			csrc += len - 1;
			while (len--)
				*cdst-- = *csrc--;
		}
		else
			ft_memcpy(dst, src, len);
	}
	return (dst);
}

/**
 * Writes len bytes of value c to the string b.
 * @param b Void pointer converted to an unsigned char pointer.
 * @param c Int value of character converted to unsigned char.
 * @returns Returns b.
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*z;
	unsigned char	ch;

	if (b)
	{
		i = 0;
		z = (unsigned char *)b;
		ch = (unsigned char)c;
		while (i < len)
		{
			z[i] = ch;
			i++;
		}
	}
	return (b);
}
