/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_converts.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 17:04:24 by dliu          #+#    #+#                 */
/*   Updated: 2023/04/10 16:09:10 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 040);
	return (c);
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 040);
	return (c);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	neg;

	num = 0;
	neg = 1;
	while (*str != '\0' && ft_strchr(" \t\n\v\f\r", *str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * neg);
}

long long	ft_atoll(const char *str)
{
	long long	num;
	int			neg;

	num = 0;
	neg = 1;
	while (*str != '\0' && ft_strchr(" \t\n\v\f\r", *str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = (num * 10) + (*str - '0');
		str++;
	}
	return (num * neg);
}
