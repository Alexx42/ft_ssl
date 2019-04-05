/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wap.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 14:17:40 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 10:49:32 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_zero(char **arr, t_flags **flags)
{
	if ((*arr)[0] == '0' && (*flags)->len == 1)
		(*flags)->zeros += 1;
}

int		width(t_list **lst, t_flags *flags, char **arr, const char *fmt)
{
	int i[2];
	int len;
	int count;

	i[1] = flags->len;
	i[0] = 0;
	count = precision_width(flags);
	len = get_len(lst, flags, arr, fmt);
	if (flags->width > flags->precision && flags->width > 0)
	{
		if (flags->minus == 0)
			while (i[0]++ < ((flags->width) - count) - (len))
				width_zminus(lst, flags, len);
		else if (flags->minus)
		{
			flags->precision - flags->len == 1 ? append_pf(lst, "0", 1) : 0;
			while (i[0] < (flags->width - count) - len && flags->len >= 0)
			{
				arr_width(&flags, arr, i);
				i[0]++;
			}
			(*arr)[flags->len + i[0]] = '\0';
		}
	}
	return (flags->precision) > 0 ? precision_handle(lst, flags, arr) : len;
}

void	value_negative(char **arr, t_list **lst, t_flags **flags)
{
	int i;

	i = 0;
	if (*arr && arr)
	{
		if (*arr[0] == '-' && ((*flags)->len_total > 0 || (*flags)->o_flag > 0
		|| (*flags)->precision > (*flags)->len))
		{
			while (i < (*flags)->len - 1)
			{
				(*arr)[i] = (*arr)[i + 1];
				i++;
			}
			(*arr)[i] = '\0';
			(*flags)->len--;
			(*flags)->neg = 1;
			append_pf(lst, "-", 1);
		}
	}
}

void	value_zero(char **arr, t_flags **flags, const char *fmt)
{
	if (*arr[0] == '0' && (*flags)->len == 1 && ((*flags)->dot == 1 ||
		(*flags)->precision == 0) && ((*flags)->flags_2 == 2 || ((*fmt == 'x' &&
		(*flags)->precision == 0)) || ((*fmt == 'o' && (*flags)->precision == 0
		&& (*flags)->hash == 0)) || (((*flags)->dot == 1 && *fmt == 'd'))))
	{
		*arr[0] = '\0';
		(*flags)->len--;
	}
}

int		precision_handle(t_list **lst, t_flags *flags, char **arr)
{
	int i[2];

	i[0] = 0;
	if (!(*arr) || !arr)
		return (0);
	if (ft_atoi(*arr) != 0 || (ft_atoi(*arr) == 0 && flags->len == 1))
		precision_nb(lst, flags, i[0]);
	else if (ft_atoi(*arr) == 0)
	{
		i[1] = flags->len;
		precision_str(lst, flags, arr, i);
		i[0] = 0;
		i[1] = flags->len;
		while (i[0] < i[1] - flags->precision)
		{
			(*arr)[i[0] + i[1] - flags->precision] = 0;
			flags->len--;
			i[0]++;
		}
		flags->len += -1;
		while (++flags->len < flags->width && flags->minus == 1)
			(*arr)[flags->len] = ' ';
	}
	return (i[0]);
}
