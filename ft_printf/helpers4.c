/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 22:39:33 by ale-goff          #+#    #+#             */
/*   Updated: 2018/10/10 22:39:34 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	valid_free(int *len, t_flags *flags, char **arr, t_list **lst)
{
	check_null(len, arr);
	free_content(flags, lst, (*arr));
}

void	init_beg(t_list **lst, int *i)
{
	(*i) = 0;
	(*lst) = NULL;
}

void	non_conversion(const char *fmt, char *buf, int *i)
{
	buf[(*i)] = *fmt;
	(*i)++;
}
