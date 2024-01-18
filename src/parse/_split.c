/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   _split.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:48:52 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/18 11:56:02 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	split_count(const char *s);
static int		split_extract(t_split *split);
static int		handle_quote(t_split *split);
static int		safe_copy(t_split	*split);

/**
 * Splits a string into an array of strings allocated (with malloc(3)).
 * Uses space as delimiter while respecting and removing quotation marks.
 * @param s The string to be split.
 * @return The array of new strings ending with a NULL pointer
 * or NULL if the allocation fails.
*/
char	**_split(char *s)
{
	t_split	split;
	size_t	count;

	count = split_count(s);
	if (!count)
		return (NULL);
	split.str = s;
	split.tmp = NULL;
	split.result = ft_calloc((count + 1), sizeof(*split.result));
	if (split.result && split_extract(&split) == SUCCESS)
		return (split.result);
	ft_free_strarr(split.result);
	return (NULL);
}

static size_t	split_count(const char *s)
{
	size_t	count;

	count = 0;
	while (s && *s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
			count++;
		while (*s && !ft_isspace(*s))
		{
			if (ft_isquote(*s))
			{
				s = ft_strchr(s + 1, *s);
				if (!s)
					return (0);
			}
			s++;
		}
	}
	return (count);
}

static int	split_extract(t_split *split)
{
	size_t	i;

	i = 0;
	while (*split->str)
	{
		while (ft_isspace(*split->str))
			split->str++;
		split->pos = split->str;
		while (*split->pos && !ft_isspace(*split->pos))
		{
			if (!ft_isquote(*split->pos))
				split->pos++;
			else if (handle_quote(split) != SUCCESS)
				return (MALLOC_ERROR);
		}
		if (safe_copy(split) != SUCCESS)
			return (MALLOC_ERROR);
		split->result[i] = split->tmp;
		split->tmp = NULL;
		i++;
	}
	return (SUCCESS);
}

static int	handle_quote(t_split *split)
{
	if (safe_copy(split) != SUCCESS)
		return (MALLOC_ERROR);
	split->str++;
	split->pos = ft_strchr(split->str, *split->pos);
	if (safe_copy(split) != SUCCESS)
		return (MALLOC_ERROR);
	split->pos++;
	split->str = split->pos;
	return (SUCCESS);
}

static int	safe_copy(t_split	*split)
{
	char	*substr;

	if (split->pos <= split->str)
		return ((SUCCESS));
	substr = ft_substr(split->str, 0, split->pos - split->str);
	if (substr)
		split->tmp = ft_strcat_free(split->tmp, substr);
	if (!split->tmp)
		return (MALLOC_ERROR);
	split->str = split->pos;
	return (SUCCESS);
}
