/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_nonlinear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 08:43:34 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 09:29:08 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

uint32_t		f_func(int b, int c, int d)
{
	return ((b & c) | ((~b) & d));
}

uint32_t		g_func(int b, int c, int d)
{
	return ((d & b) | (c & (~d)));
}

uint32_t		h_func(int b, int c, int d)
{
	return (b ^ c ^ d);
}

uint32_t		i_func(int b, int c, int d)
{
	return (c ^ (b | (~d)));
}
