/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 16:28:54 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 10:49:32 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(const char *str)
{
	int							i;
	unsigned long long int		num;
	int							sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (num > 9223372036854775807 && sign == -1)
		return (0);
	else if (num > 9223372036854775807)
		return (-1);
	return (sign * num);
}

void	precision_nb(t_list **lst, t_flags *flags, int i)
{
	while (i < flags->precision - flags->len + flags->zeros)
	{
		append_pf(lst, "0", 1);
		i++;
	}
}

void	precision_str(t_list **lst, t_flags *flags, char **arr, int i[2])
{
	while (i[0] < flags->precision && flags->width > flags->precision &&
	flags->len > 0)
	{
		if (flags->minus == 0)
			append_pf(lst, " ", 1);
		else if (flags->minus == 1)
		{
			if (flags->width > flags->precision && flags->width >
			flags->len)
				append_pf(lst, " ", 1);
			else
			{
				(*arr)[i[0] + i[1]] = ' ';
				flags->len++;
			}
		}
		i[0]++;
	}
}

void	check_null(int *len, char **arr)
{
	if (*arr == NULL)
	{
		*len += 1;
		*arr = malloc(1);
		**arr = 0;
	}
}

void	renew(int *len, const char **fmt, t_list **lst)
{
	(*fmt)++;
	print_list((*lst));
	*len += list_size((*lst));
	delete_list(lst);
}
