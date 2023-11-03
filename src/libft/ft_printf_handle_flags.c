/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_handle_flags.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 16:17:12 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/01 16:02:27 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_width(int *width, const char *format)
{
	int		i;
	char	buffer[11];
	char	*pos;

	i = 0;
	pos = buffer;
	while (ft_isdigit(format[i]) && i < 11)
	{
		*pos = format[i];
		pos++;
		i++;
	}
	*pos = '\0';
	*width = ft_atoi(buffer);
	return (i);
}

int	set_flags(t_print *tab, const char *format)
{
	int		i;

	i = 0;
	while (format[i] && ft_strchr("-+ #0", format[i]))
	{
		if (format[i] == '-')
			tab->dash = 1;
		if (format[i] == '+')
			tab->plus = 1;
		if (format[i] == ' ')
			tab->space = 1;
		if (format[i] == '#')
			tab->hash = 1;
		if (format[i] == '0')
			tab->zero = 1;
		i++;
	}
	i += set_width(&(tab->w_min), &format[i]);
	if (format[i] == '.')
	{
		tab->dot = 1;
		i++;
		i += set_width(&(tab->w_precise), &format[i]);
	}
	return (i);
}

void	apply_flags_chars(t_print *tab)
{
	char	*content;
	char	*extra;
	int		len;

	if (tab->w_min || tab->dot)
	{
		content = tab->plist->content;
		extra = NULL;
		len = ft_biggest(ft_strlen(content), 1);
		if (tab->dot && (len - tab->w_precise) > 0)
		{
			content[tab->w_precise] = '\0';
			tab->iszero = 1;
		}
		len = ft_strlen(content);
		if (tab->plus)
			len = ft_biggest(ft_strlen(content), 1);
		tab->w_min -= len;
		if (tab->w_min > 0)
		{
			extra = ft_strrep(' ', tab->w_min);
			add_node(tab, extra, tab->dash);
		}
	}
}

void	apply_flags_hex(t_print *tab)
{
	char	*extra;

	if (tab->isneg)
		extra = ft_strdup("0X");
	else
		extra = ft_strdup("0x");
	add_node(tab, extra, 0);
}
