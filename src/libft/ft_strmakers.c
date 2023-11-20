/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmakers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 19:03:29 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/20 11:41:00 by codespace     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Allocates (with malloc(3)) and returns a duplicate of a string
char	*ft_strdup(const char *s1)
{
	char	*string;
	size_t	len;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	string = ft_calloc(len + 1, sizeof(*string));
	if (string != NULL)
	{
		ft_memcpy(string, s1, len);
		return (string);
	}
	return (NULL);
}

//Joins two strings. Allocates (with malloc(3)).
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(len, sizeof (*str));
	if (str == NULL)
		return (NULL);
	if (s1 && *s1)
		ft_strlcpy(str, s1, len);
	if (s2)
		ft_strlcat(str, s2, len);
	return (str);
}

/**
 * Allocates (with malloc(3)) and returns a substring from a string.
 * @param s The string from which to create the substring.
 * @param start The start index of the substrign in the string 's'
 * @param len The maximum length of the substring.
 * @returns The substring. NULL if the allocation fails.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	size_t			size;

	str = NULL;
	if (s)
	{
		size = ft_strlen(s);
		if (size <= start)
			len = 0;
		else if (size - start < len)
			len = size - start;
		str = ft_calloc(len + 1, sizeof(*str));
		if (!str)
			return (NULL);
		if (size == 0 || len == 0)
			str[0] = '\0';
		else
			ft_strlcpy(str, &s[start], len + 1);
	}
	return (str);
}

/**
 * Allocates (with malloc(3)) and returns a copy of s1 with chars in set removed
 * from the beginning and end of the string.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char		*string;
	size_t		start;
	size_t		len;

	string = NULL;
	if (s1 != NULL && set != NULL)
	{
		start = 0;
		len = ft_strlen(s1);
		while (s1[start] != '\0' && ft_strchr(set, s1[start]))
			start++;
		if (len == 0 || start == len)
			len = 1;
		else
		{
			while (ft_strchr(set, s1[len - 1]))
				len--;
			len = len - start;
		}
		string = ft_substr(s1, start, len);
	}
	return (string);
}

//Allocates (with malloc(3)) and returns a string with repeating characters.
char	*ft_strrep(const char c, const size_t len)
{
	char	*str;

	str = ft_calloc(len + 1, sizeof(*str));
	if (str)
		ft_memset(str, c, len);
	return (str);
}
