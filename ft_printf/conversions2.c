/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 15:02:46 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 10:45:40 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*conversion_z(const char *str, va_list args)
{
	char c;

	c = *str;
	if (c == 'd' || c == 'i')
		return (ft_itoa_base_signed((va_arg(args, size_t)), 10, 0));
	else if (c == 'c' || c == 'C')
		return (ft_chartostr((char)va_arg(args, int)));
	else if (c == 's')
		return (ft_strdup_pf(va_arg(args, char*)));
	else if (c == 'S')
		return (ft_strdup_wchar(va_arg(args, wchar_t*)));
	else if (c == 'o' || c == 'O')
		return (ft_itoa_base(va_arg(args, size_t), 8, 0));
	else if (c == 'x' || c == 'X')
		return (ft_itoa_base(va_arg(args, size_t), 16, c == 'X'));
	else if (c == 'u' || c == 'D')
		return (ft_itoa_base((va_arg(args, size_t)), 10, 0));
	else if (c == 'U')
		return (ft_itoa_base((va_arg(args, unsigned long)), 10, 0));
	else if (c == 'p')
		return (ft_strjoin_pf("0x", ft_itoa_base(va_arg(args, unsigned long),
		16, 0)));
	else
		return (ft_chartostr(c));
}

char	*conversion_l(const char *str, va_list args)
{
	char c;

	c = *str;
	if (c == 'd' || c == 'i')
		return (ft_itoa_base_signed((va_arg(args, long int)), 10, 0));
	else if (c == 'c' || c == 'C')
		return (ft_chartostr((wint_t)va_arg(args, wint_t)));
	else if (c == 's')
		return (ft_strdup_wchar(va_arg(args, wchar_t*)));
	else if (c == 'o' || c == 'O')
		return (ft_itoa_base(va_arg(args, unsigned long int), 8, 0));
	else if (c == 'x' || c == 'X')
		return (ft_itoa_base(va_arg(args, unsigned long int), 16, c == 'X'));
	else if (c == 'u' || c == 'D')
		return (ft_itoa_base((va_arg(args, unsigned long int)), 10, 0));
	else if (c == 'U')
		return (ft_itoa_base((va_arg(args, unsigned long)), 10, 0));
	else if (c == 'p')
		return (ft_strjoin_pf("0x", ft_itoa_base(va_arg(args, unsigned long),
		16, 0)));
	else
		return (ft_chartostr(c));
}

char	*conversion_j(const char *str, va_list args)
{
	char c;

	c = *str;
	if (c == 'd' || c == 'i')
		return (ft_itoa_base_signed((va_arg(args, intmax_t)), 10, 0));
	else if (c == 'c' || c == 'C')
		return (ft_chartostr((char)va_arg(args, int)));
	else if (c == 's')
		return (ft_strdup_pf(va_arg(args, char*)));
	else if (c == 'o' || c == 'O')
		return (ft_itoa_base(va_arg(args, uintmax_t), 8, 0));
	else if (c == 'x' || c == 'X')
		return (ft_itoa_base(va_arg(args, uintmax_t), 16, c == 'X'));
	else if (c == 'u' || c == 'D')
		return (ft_itoa_base((va_arg(args, uintmax_t)), 10, 0));
	else if (c == 'U')
		return (ft_itoa_base((va_arg(args, unsigned long)), 10, 0));
	else if (c == 'p')
		return (ft_strjoin_pf("0x", ft_itoa_base(va_arg(args, unsigned long),
		16, 0)));
	else
		return (ft_chartostr(c));
}

char	*conversion_ll(const char *str, va_list args)
{
	char c;

	c = *str;
	if (c == 'd' || c == 'i')
		return (ft_itoa_base_signed((va_arg(args, long long int)), 10, 0));
	else if (c == 'c' || c == 'C')
		return (ft_chartostr((char)va_arg(args, int)));
	else if (c == 's')
		return (ft_strdup_pf(va_arg(args, char*)));
	else if (c == 'o' || c == 'O')
		return (ft_itoa_base(va_arg(args, unsigned long long int), 8, 0));
	else if (c == 'x' || c == 'X')
		return (ft_itoa_base(va_arg(args, unsigned long long int), 16,
		c == 'X'));
	else if (c == 'u' || c == 'D')
		return (ft_itoa_base((va_arg(args, unsigned long long int)), 10, 0));
	else if (c == 'U')
		return (ft_itoa_base((va_arg(args, unsigned long)), 10, 0));
	else if (c == 'p')
		return (ft_strjoin_pf("0x", ft_itoa_base(va_arg(args, unsigned long),
		16, 0)));
	else
		return (ft_chartostr(c));
}
