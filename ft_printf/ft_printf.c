/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 18:13:49 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 10:49:32 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf.h"

int			ft_printf(const char *fmt, ...)
{
	va_list		args;
	t_list		*lst;
	char		buf[4096];
	int			len;

	len = 0;
	va_start(args, fmt);
	lst = elem_list(fmt, buf, &len, args);
	len += list_size(lst);
	print_list(lst);
	delete_list(&lst);
	return (len);
}

t_list		*elem_list(const char *fmt, char *buf, int *len, va_list args)
{
	char	*arr;
	t_flags	*flags;
	t_list	*lst;
	int		i;

	init_beg(&lst, &i);
	while (*fmt)
	{
		lst = NULL;
		if (*fmt == '%')
		{
			get_values(buf, i, &fmt, &flags);
			append_pf(&lst, buf, i);
			init_values(&i, &arr);
			arr = choose_conversion(flags, fmt, args);
			assign_value(fmt, &flags, &lst, &arr);
			valid_free(len, flags, &arr, &lst);
		}
		else
			non_conversion(fmt, buf, &i);
		renew(len, &fmt, &lst);
	}
	buf[i] = '\0';
	append_pf(&lst, buf, i);
	return (lst);
}
