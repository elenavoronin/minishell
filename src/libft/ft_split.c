/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:48:52 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/13 16:38:17 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	split_count(const char *s, char c);
static char		**split(const char *s, char c, char **strings, size_t count);

/**
 * Splits a string into an array of strings allocated (with malloc(3)).
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings ending with a NULL pointer
 * or NULL if the allocation fails.
*/
char	**ft_split(const char *s, char c)
{
	char	**strings;
	size_t	count;

	if (s == NULL)
		return (NULL);
	count = split_count(s, c);
	strings = ft_malloc_wrapper(sizeof (*strings) * (count + 1));
	if (strings != NULL)
		strings = split(s, c, strings, count);
	return (strings);
}

static size_t	split_count(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			count++;
			while (*s != '\0' && *s != c)
				s++;
		}
		while (*s != '\0' && *s == c)
			s++;
	}
	return (count);
}

static char	**split(const char *s, char c, char **strings, size_t count)
{
	const char	*curr_pos;
	size_t		s_i;

	s_i = 0;
	while (*s && s_i < count)
	{
		while (*s != '\0' && *s == c)
			s++;
		curr_pos = s;
		while (*curr_pos != '\0' && *curr_pos != c)
			curr_pos++;
		if (curr_pos != s)
		{
			strings[s_i] = ft_substr(s, 0, curr_pos - s);
			if (strings[s_i] == NULL)
			{
				ft_free_strarr(strings);
				return (NULL);
			}
			s_i++;
			s = curr_pos;
		}
	}
	strings[s_i] = NULL;
	return (strings);
}
