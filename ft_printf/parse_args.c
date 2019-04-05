/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 10:31:00 by ale-goff          #+#    #+#             */
/*   Updated: 2018/09/25 23:19:27 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags		*init_list(void)
{
	t_flags *flags;

	flags = malloc(sizeof(t_flags));
	flags->space = 0;
	flags->plus = 0;
	flags->o_flag = 0;
	flags->minus = 0;
	flags->hash = 0;
	flags->numbers = 0;
	flags->one_h = 0;
	flags->one_l = 0;
	flags->one_j = 0;
	flags->one_l = 0;
	flags->one_z = 0;
	flags->double_l = 0;
	flags->double_h = 0;
	flags->width = 0;
	flags->precision = -1;
	flags->dot = 0;
	flags->len = 0;
	flags->len_total = 0;
	flags->zeros = 0;
	flags->flags_2 = 0;
	flags->neg = 0;
	return (flags);
}

void		parse_args(t_flags **flags, const char **fmt)
{
	while (validate_flags(**fmt))
	{
		if (**fmt == ' ')
			(*flags)->space = 1;
		else if (**fmt == '+')
			(*flags)->plus = 1;
		else if (**fmt == '-')
			(*flags)->minus = 1;
		else if (**fmt == '#')
			(*flags)->hash = 1;
		else if (**fmt == '0')
			(*flags)->o_flag = 1;
		(*fmt)++;
	}
}

void		parse_args_precision(t_flags **flags, const char **fmt)
{
	while (validate_precision(**fmt))
	{
		if (**fmt != '.' && (*flags)->dot == 0)
		{
			if (**fmt >= '0' && **fmt <= '9')
			{
				(*flags)->width = (*flags)->width * 10 + **fmt - '0';
			}
		}
		else if (**fmt == '.')
		{
			(*flags)->dot = 1;
			(*flags)->precision = 0;
		}
		else if (is_number(**fmt))
			(*flags)->precision = (*flags)->precision * 10 + **fmt - '0';
		(*fmt)++;
	}
}

void		parse_args_modifier(t_flags **flags, const char **fmt)
{
	while (validate_modifier(**fmt))
	{
		parse_modifier_helper(flags, fmt);
		(*fmt)++;
	}
}

void		parse_modifier_helper(t_flags **flags, const char **fmt)
{
	if (**fmt == 'h')
	{
		(*fmt)++;
		if (**fmt == 'h')
			(*flags)->double_h = 1;
		else
		{
			(*flags)->one_h = 1;
			(*fmt)--;
		}
	}
	else if (**fmt == 'l')
	{
		(*fmt)++;
		if (**fmt == 'l')
			(*flags)->double_l = 1;
		else
		{
			(*flags)->one_l = 1;
			(*fmt)--;
		}
	}
	(*flags)->one_j = (**fmt == 'j') ? 1 : 0;
	(*flags)->one_z = (**fmt == 'z') ? 1 : 0;
}
