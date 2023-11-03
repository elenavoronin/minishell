/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 17:08:51 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/02 18:31:23 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	initialise_tab(t_print *tab, int count);
static int	evaluate_format(t_print *tab, const char *format);
static int	print_remaining(t_print *tab, const char *format);

int	ft_printf(const char *format, ...)
{
	t_print	tab;
	int		count;

	count = -1;
	if (format)
	{
		initialise_tab(&tab, 0);
		va_start(tab.argsp, format);
		while (*format && tab.count > -1)
		{
			if (*format == '%' && ++format)
				format += evaluate_format(&tab, format);
			else if (*format)
				format += print_remaining(&tab, format);
			count = tab.count;
			ft_lstclear(&(tab.plist), ft_free);
			initialise_tab(&tab, count);
		}
		va_end(tab.argsp);
		count = tab.count;
		ft_lstclear(&(tab.plist), ft_free);
	}
	return (count);
}

static void	initialise_tab(t_print *tab, int count)
{
	tab->plist = NULL;
	tab->count = count;
	tab->isneg = 0;
	tab->iszero = 0;
	tab->plus = 0;
	tab->hash = 0;
	tab->space = 0;
	tab->dash = 0;
	tab->zero = 0;
	tab->dot = 0;
	tab->w_min = 0;
	tab->w_precise = 0;
}

static int	evaluate_format(t_print *tab, const char *format)
{
	int	i;

	i = set_flags(tab, format);
	if (format[i] == '%' || format[i] == 'c')
		print_char(tab, format[i]);
	else if (format[i] == 's')
		print_string(tab);
	else if (format[i] == 'd' || format[i] == 'i' || format[i] == 'u')
		print_int(tab, format[i]);
	else if (format[i] == 'x' || format[i] == 'X')
		print_hex(tab, format[i]);
	else if (format[i] == 'p')
		print_pnt(tab);
	else
		return (0);
	return (i + 1);
}

static int	print_remaining(t_print *tab, const char *format)
{
	int		len;
	int		count;
	char	*end;

	end = ft_strchr(format, '%');
	if (end)
		len = end - format;
	else
		len = ft_strlen(format);
	count = write(1, format, len);
	if (count < 0)
	{
		tab->count = -1;
		return (0);
	}
	tab->count += count;
	return (count);
}
