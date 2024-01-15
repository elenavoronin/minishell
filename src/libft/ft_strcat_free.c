/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strcat_free.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 14:19:51 by dliu          #+#    #+#                 */
/*   Updated: 2024/01/15 14:22:19 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Joins two strings, freeing both inputs and returning a new allocated string.
*/
char	*ft_strcat_free(char *old, char *join)
{
	char	*new;

	new = ft_strjoin(old, join);
	free(old);
	free(join);
	return (new);
}
