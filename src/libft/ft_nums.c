/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nums.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/04 20:59:48 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/01 15:34:22 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

//Returns absolute distance between a and b
size_t	ft_distance(int a, int b)
{
	long long	dist;

	dist = a - b;
	if (dist < 0)
		dist *= -1;
	return (dist);
}

//If the input is negative, returns it as a positive
int	ft_abs(int num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

//Counts and returns the length of the number n in the given base.
int	ft_numlen(long long n, int base)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

//Compares a to b and returns the smallest value, or a if they are equal.
int	ft_smallest(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

//Compares a to b and returns the biggest value, or a if they are equal.
int	ft_biggest(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}
