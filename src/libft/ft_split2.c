/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:48:52 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/16 17:43:29 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	split_count(char *s);
static char		*extract(char **s);

/**
 * Splits a string into an array of strings allocated with malloc(3).
 * Splits will be delimited by white spaces, unless within quotation marks.
 * returns NULL if void or empty string.
*/
char	**ft_split2(char *s)
{
	char	**strings;
	size_t	i;
	size_t	count;

	count = split_count(s);
	if (!count)
		return (NULL);
	strings = ft_calloc((count + 1), sizeof(*strings));
	if (!strings)
		return (NULL);
	i = 0;
	while (i < count)
	{
		strings[i] = extract(&s);
		if (!strings[i])
			return (ft_free_strarr(strings), NULL);
		i++;
	}
	strings[count] = NULL;
	return (strings);
}

static size_t	split_count(char *s)
{
	size_t	count;

	count = 0;
	while (s && *s)
	{
		while (ft_isspace(*s))
			s++;
		if (ft_isquote(*s))
		{
			count++;
			s = ft_strchr(s + 1, *s);
			if (!s)
				return (0);
			s++;
		}
		else
		{
			count++;
			while (*s && !ft_isquote(*s) && !ft_isspace(*s))
				s++;
		}
	}
	return (count);
}

static char	*extract(char **s)
{
	char	*pos;
	char	*string;

	while (**s && ft_isspace(**s))
		*s += 1;
	if (ft_isquote(**s))
	{
		pos = ft_strchr(*s + 1, **s);
		*s += 1;
		string = ft_substr(*s, 0, pos - *s);
		*s = pos + 1;
	}
	else
	{
		pos = *s;
		while (*pos && !ft_isspace(*pos) && !ft_isquote(*pos))
			pos++;
		string = ft_substr(*s, 0, pos - *s);
		*s = pos;
	}
	if (!string)
		return (NULL);
	return (string);
}
