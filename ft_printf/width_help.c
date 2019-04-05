/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:06:25 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 10:49:32 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_len(t_list **lst, t_flags *flags, char **arr, const char *fmt)
{
	int len;

	if (flags->hash)
		len = hash_flags(lst, fmt, arr);
	else
		len = flags->len_total;
	protect_value(lst, &flags, arr);
	return (len);
}

void	width_zminus(t_list **lst, t_flags *flags, int len)
{
	int i;

	i = flags->len;
	if (flags->o_flag && flags->precision > 0)
		flags->o_flag = 0;
	if (flags->o_flag && len == 0)
	{
		if (flags->width - flags->precision != i && flags->precision > 0)
			append_pf(lst, " ", 1);
		else
			append_pf(lst, "0", 1);
	}
	else if (flags->o_flag && len > 0)
		append_pf(lst, "0", 1);
	else if ((flags->plus || flags->hash) && flags->o_flag == 0)
		push(lst, " ", 1);
	else if (flags->neg == 0)
		append_pf(lst, " ", 1);
}

void	protect_value(t_list **lst, t_flags **flags, char **arr)
{
	if (*arr)
		parse_zero(arr, flags);
	if (*arr)
		value_negative(arr, lst, flags);
}

int		precision_width(t_flags *flags)
{
	return ((flags->precision > flags->len && flags->len > 0) ?
			(flags->precision) : flags->len);
}

void	arr_width(t_flags **flags, char **arr, int i[2])
{
	(*arr)[i[1] + i[0] - (*flags)->neg] = ' ';
	(*flags)->len++;
}
