/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_handle_flags_nums.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dliu <dliu@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/01 16:17:12 by dliu          #+#    #+#                 */
/*   Updated: 2023/11/01 16:02:24 by dliu          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	apply_num_space(t_print *tab, int *minpad);
static void	apply_num_sign(t_print *tab);
static void	apply_num_zero(t_print *tab, int *pad);
static void	apply_num_dot(t_print *tab, int maxpad, int *minpad);

void	apply_flags_num(t_print *tab)
{
	int		minpad;
	int		len;

	if (tab->plist->content)
	{
		len = ft_strlen(tab->plist->content);
		minpad = tab->w_min - len;
		if (tab->dot)
			apply_num_dot(tab, ft_biggest(tab->w_precise - len, 0), &minpad);
		else if (!tab->dash && tab->zero && minpad > 0)
			apply_num_zero(tab, &minpad);
		if (tab->count > -1 && tab->hash && !tab->iszero)
			apply_flags_hex(tab);
		if (tab->count > -1 && !tab->hash && (tab->isneg || tab->plus))
		{
			apply_num_sign(tab);
			minpad -= 1;
		}
		if (tab->count > -1 && (tab->space || minpad > 0))
		{
			if (tab->hash && !tab->iszero)
				minpad -= 2;
			apply_num_space(tab, &minpad);
		}
	}
}

static void	apply_num_space(t_print *tab, int *minpad)
{
	char	*extra;

	if (!tab->plus && !tab->isneg && tab->space)
	{
		extra = ft_strdup(" ");
		add_node(tab, extra, 0);
		*minpad -= 1;
	}
	if (*minpad > 0 && tab->count > -1)
	{
		extra = ft_strrep(' ', *minpad);
		add_node(tab, extra, tab->dash);
	}
}

static void	apply_num_sign(t_print *tab)
{
	char	*extra;

	if (tab->isneg)
	{
		extra = ft_strdup("-");
		add_node(tab, extra, 0);
	}
	else
	{
		extra = ft_strdup("+");
		add_node(tab, extra, 0);
	}
}

static void	apply_num_zero(t_print *tab, int *pad)
{
	char	*extra;

	if (tab->hash && !tab->iszero && !tab->dot)
		*pad -= 2;
	if ((tab->space || tab->isneg || tab->plus) && !tab->dot && !tab->hash)
		*pad -= 1;
	if (*pad > 0)
	{
		extra = ft_strrep('0', *pad);
		add_node(tab, extra, 0);
	}
	*pad = 0;
}

static void	apply_num_dot(t_print *tab, int maxpad, int *minpad)
{
	if (tab->iszero && maxpad == 0 && tab->w_precise < 1)
	{
		free(tab->plist->content);
		tab->plist->content = NULL;
		*minpad += 1;
		return ;
	}
	if (maxpad > *minpad)
		*minpad = 0;
	else
		*minpad -= maxpad;
	apply_num_zero(tab, &maxpad);
}
