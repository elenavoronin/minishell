/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_joinstrs.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/20 13:31:04 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/01 15:23:14 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Uses malloc, joins multiple strings together.
 * @param count The amount of strings to join.
*/
char	*ft_joinstrs(int count, ...)
{
	int		i;
	char	*tmp;
	char	*joined;
	char	*string;
	va_list	args;

	va_start(args, count);
	i = 0;
	joined = NULL;
	while (i < count)
	{
		string = va_arg(args, char *);
		if (!string)
		{
			free(joined);
			return (NULL);
		}
		tmp = ft_strjoin(joined, string);
		free(joined);
		joined = tmp;
		i++;
	}
	va_end(args);
	return (joined);
}
