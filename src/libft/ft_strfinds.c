/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strfinds.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:10:10 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/02 14:51:47 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Locates the first occurrence of c (converted to a char) in a string.
 * @param s Pointer to first character in a string.
 * @param c The character to locate.
 * @returns A pointer to the located character or NULL if it does not appear.
*/
char	*ft_strchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	return (ft_memchr(s, c, len + 1));
}

/**
 * Locates the last occurrence of c (converted to a char) in a string.
 * @param s Pointer to first character in a string.
 * @param c The character to locate.
 * @returns A pointer to the located character or NULL if it does not appear.
*/
char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	size_t			end;

	end = ft_strlen(s) + 1;
	ch = (unsigned char)c;
	s += end - 1;
	while (end-- > 0)
	{
		if (*s == ch)
			return ((char *) s);
		s--;
	}
	return (NULL);
}

/**
 * Locates the first occurrence of a string in another string.
 * @param haystack The string to search in.
 * @param needle The string to locate.
 * @param len The maximum length to search.
 * @returns Haystack if needle is empty. Null if Needle not found.
 * Else pointer to the first character of the first occurrence of needle.
*/
char	*ft_strnstr(const char *haystack, const char*needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (i + j < len && haystack[i + j] == needle[j])
		{
			j++;
			if (needle[j] == '\0')
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}

/**
 * Lexicographically compares two strings.
 * @returns The difference between the strings if found or 0 if no diff found.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if ((s1 && !s2) || (s2 && !s1))
			return (-1);
		if (s1[i] != s2[i] || s1[i] == '\0')
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/**
 * Compares two strings until a difference, or '\0' is found in either string.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	if (!s1 || !s2)
	{
		if (s1 != s2)
			return (444);
		return (0);
	}
	while(s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
