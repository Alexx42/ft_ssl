/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:58:06 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 10:49:32 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		hash_flags(t_list **lst, const char *fmt, char **arr)
{
	int len;

	len = 0;
	if (arr == NULL || *arr == NULL)
		return (0);
	if (*fmt == 'o')
		len = 1;
	else if (*fmt == 'x' || *fmt == 'X')
		len = 2;
	if (*fmt == 'o' && ft_atoi(*arr) != 0)
		append_pf(lst, "0", 1);
	else if (*fmt == 'x' && ft_atoi(*arr) != 0)
		append_pf(lst, "0x", 2);
	else if (*fmt == 'X' && ft_atoi(*arr) != 0)
		append_pf(lst, "0X", 2);
	return (len);
}

int		plus_flags(t_list **lst)
{
	append_pf(lst, "+", 1);
	return (1);
}

int		space_flags(t_list **lst)
{
	append_pf(lst, " ", 1);
	return (1);
}

int		handle_flags(t_list **lst, t_flags *flags, char *arr)
{
	if (flags->plus && (ft_atoi(arr) > 0 || ft_atoi(arr) == 0))
		return (plus_flags(lst));
	else if (flags->space && (arr == NULL || ft_atoi(arr) > 0) &&
	flags->plus == 0 && flags->len != 1)
		return (space_flags(lst));
	return (0);
}

int		handle_flags2(t_list **lst, t_flags *flags, char **arr, const char *fmt)
{
	if (flags->width >= 0)
		return (width(lst, flags, arr, fmt));
	return (0);
}
