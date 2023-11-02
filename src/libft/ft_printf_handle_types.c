/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_handle_types.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 16:17:12 by dliu          #+#    #+#                 */
/*   Updated: 2022/12/12 14:55:30 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_char(t_print *tab, const char c)
{
	char	buffer[2];
	char	*content;

	if (c == '%')
		buffer[0] = '%';
	else if (c == 'c')
		buffer[0] = va_arg(tab->argsp, int);
	buffer[1] = '\0';
	content = ft_strdup(buffer);
	if (!add_node(tab, content, 0))
		return ;
	tab->dot = 0;
	tab->plus = 1;
	apply_flags_chars(tab);
	check_write(tab);
}

void	print_string(t_print *tab)
{
	char	*buffer;
	char	*content;

	buffer = va_arg(tab->argsp, char *);
	if (buffer)
	{
		if (*buffer == '\0')
			tab->iszero = 1;
		content = ft_strdup(buffer);
	}
	else
		content = ft_strdup("(null)");
	if (!add_node(tab, content, 0))
		return ;
	apply_flags_chars(tab);
	check_write(tab);
}

void	print_int(t_print *tab, const char c)
{
	char		*content;
	long long	number;

	if (c == 'd' || c == 'i')
		number = va_arg(tab->argsp, int);
	else
		number = va_arg(tab->argsp, unsigned int);
	if (number == 0)
		tab->iszero = 1;
	if (number < 0)
	{
		tab->isneg = 1;
		number = -number;
	}
	content = ft_lltoa_base(number, 10);
	if (!add_node(tab, content, 0))
		return ;
	apply_flags_num(tab);
	check_write(tab);
}

void	print_hex(t_print *tab, const char c)
{
	int				i;
	char			*content;
	long long		number;

	number = va_arg(tab->argsp, unsigned int);
	if (number == 0)
		tab->iszero = 1;
	content = ft_lltoa_base(number, 16);
	if (c == 'X' && content)
	{
		i = 0;
		while (content[i])
		{
			content[i] = ft_toupper(content[i]);
			i++;
		}
		if (tab->hash)
			tab->isneg = 1;
	}
	if (!add_node(tab, content, 0))
		return ;
	apply_flags_num(tab);
	check_write(tab);
}

void	print_pnt(t_print *tab)
{
	char			*content;
	unsigned long	number;

	tab->hash = 1;
	number = va_arg(tab->argsp, unsigned long);
	content = ft_ltoa_unsigned_base(number, 16);
	if (!add_node(tab, content, 0))
		return ;
	apply_flags_num(tab);
	check_write(tab);
}
