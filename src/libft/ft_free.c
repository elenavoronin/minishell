/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 18:02:49 by dliu          #+#    #+#                 */
/*   Updated: 2023/01/21 23:27:02 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void *content)
{
	free(content);
	content = NULL;
}

void	ft_free_strarr(char **array)
{
	size_t	i;

	if (array)
	{
		i = 0;
		while (array[i])
		{
			ft_free(array[i]);
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	ft_free_strnarr(char **array, size_t n)
{
	size_t	i;

	if (array)
	{
		i = 0;
		while (i < n)
		{
			ft_free(array[i]);
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	ft_free_strarrarr(char ***arrarr)
{
	size_t	i;

	if (arrarr)
	{
		i = 0;
		while (arrarr[i])
		{
			ft_free_strarr(arrarr[i]);
			i++;
		}
		free(arrarr);
		arrarr = NULL;
	}
}

void	ft_free_intarrarr(int **intarrarr)
{
	int	i;

	if (intarrarr)
	{
		i = 0;
		while (intarrarr[i])
		{
			free(intarrarr[i]);
			i++;
		}
		free(intarrarr);
		intarrarr = NULL;
	}
}
