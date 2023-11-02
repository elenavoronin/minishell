/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_put_fd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 14:15:56 by dliu          #+#    #+#                 */
/*   Updated: 2023/02/07 15:09:26 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putstr_col_fd(char *color, char *s, int fd)
{
	if (s == NULL)
		return ;
	ft_putstr_fd(color, fd);
	write(fd, s, ft_strlen(s));
	ft_putstr_fd(ANSI_COL_RESET, fd);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	int				len;
	unsigned int	num;
	char			numstr[12];

	len = 0;
	num = n;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
	{
		num = -n;
		ft_putchar_fd('-', fd);
	}
	len = ft_numlen(n, 10);
	numstr[len] = '\0';
	while (len > 0)
	{
		numstr[len - 1] = ('0' + (num % 10));
		num = num / 10;
		len--;
	}
	ft_putstr_fd(numstr, fd);
}
