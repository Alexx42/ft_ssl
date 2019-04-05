/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_fun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 21:25:25 by ale-goff          #+#    #+#             */
/*   Updated: 2018/09/25 22:05:18 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			validate_flags(char c)
{
	if (c == '#' || c == '-' || c == '+' || c == '0' || c == ' ')
		return (1);
	return (0);
}

int			validate_precision(char c)
{
	if ((c >= '0' && c <= '9') || c == '.')
		return (1);
	return (0);
}

int			is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			validate_percentage(char c)
{
	if (c == 'D' || c == 'd' || c == 'i' || c == 'o'
	|| c == 'O' || c == 'x' || c == 'X' || c == 'p')
		return (1);
	return (0);
}

int			validate_modifier(char c)
{
	if (c == 'h' || c == 'l' || c == 'j' || c == 'z')
		return (1);
	return (0);
}
