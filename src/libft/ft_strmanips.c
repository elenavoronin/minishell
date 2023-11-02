/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmanips.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 11:20:15 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/01 15:41:03 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Applies the function f to each character of the string s and creates a new
 * string (with malloc(3)).
 * @param s The string on which to iterate.
 * @param f The funciton to apply to each character.
 * @returns The strign created from the successive application of f
 * of NULL if allocation fails.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*string;

	if (s != NULL && f != NULL)
	{
		len = ft_strlen(s);
		i = 0;
		string = ft_calloc(len + 1, sizeof(*string));
		if (string != NULL)
		{
			while (s[i] != '\0')
			{
				string[i] = f(i, s[i]);
				i++;
			}
			string[i] = '\0';
			return (string);
		}
	}
	return (NULL);
}

/**
 * Applies the function f on each char of a string.
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (s == NULL || f == NULL)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

//Reverses the string in place.
char	*ft_strrev(char *string)
{
	char	hold;
	size_t	start;
	size_t	end;
	size_t	len;

	len = ft_strlen(string);
	if (string && len > 1)
	{
		start = 0;
		end = len - 1;
		while (start < end)
		{
			hold = string[end];
			string[end] = string[start];
			string[start] = hold;
			start++;
			end--;
		}
		string[len] = '\0';
	}
	return (string);
}
