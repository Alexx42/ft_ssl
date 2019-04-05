/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 18:50:49 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 10:39:41 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_chartostr(char c)
{
	char *s;

	if (c == 0)
		return (NULL);
	s = malloc(2);
	s[0] = c;
	s[1] = '\0';
	return (s);
}

char	*conversion(const char *str, va_list args)
{
	char c;

	c = *str;
	if (c == 'd' || c == 'i')
		return (ft_itoa_base_signed((va_arg(args, int)), 10, 0));
	else if (c == 'c' || c == 'C')
		return (ft_chartostr((char)va_arg(args, int)));
	else if (c == 's')
		return (ft_strdup_pf(va_arg(args, char*)));
	else if (c == 'o' || c == 'O')
		return (ft_itoa_base(va_arg(args, unsigned int), 8, 0));
	else if (c == 'x' || c == 'X')
		return (ft_itoa_base(va_arg(args, unsigned int), 16, c == 'X'));
	else if (c == 'u' || c == 'D')
		return (ft_itoa_base((va_arg(args, unsigned int)), 10, 0));
	else if (c == 'U')
		return (ft_itoa_base((va_arg(args, unsigned long)), 10, 0));
	else if (c == 'p')
		return (ft_strjoin_pf("0x", ft_itoa_base(va_arg(args, unsigned long),
			16, 0)));
	else
		return (ft_chartostr(c));
}

char	*conversion_h(const char *str, va_list args)
{
	char c;

	c = *str;
	if (c == 'd' || c == 'i')
		return (ft_itoa_base_signed((short int)(va_arg(args, int)), 10, 0));
	else if (c == 'c' || c == 'C')
		return (ft_chartostr((char)va_arg(args, int)));
	else if (c == 's')
		return (ft_strdup_pf(va_arg(args, char*)));
	else if (c == 'o' || c == 'O')
		return (ft_itoa_base((unsigned short)va_arg(args, unsigned int), 8, 0));
	else if (c == 'x' || c == 'X')
		return (ft_itoa_base((unsigned short int)va_arg(args, unsigned int),
			16, c == 'X'));
	else if (c == 'u' || c == 'D')
		return (ft_itoa_base((unsigned short int)(va_arg(args, unsigned int)),
			10, 0));
	else if (c == 'U')
		return (ft_itoa_base((va_arg(args, unsigned long)),
			10, 0));
	else if (c == 'p')
		return (ft_strjoin_pf("0x", ft_itoa_base(va_arg(args, unsigned long), 16,
			0)));
	else
		return (ft_chartostr(c));
}

char	*conversion_hh(const char *str, va_list args)
{
	char c;

	c = *str;
	if (c == 'd' || c == 'i')
		return (ft_itoa_base_signed((signed char)(va_arg(args, int)), 10, 0));
	else if (c == 'c' || c == 'C')
		return (ft_chartostr((char)va_arg(args, int)));
	else if (c == 's')
		return (ft_strdup_pf(va_arg(args, char*)));
	else if (c == 'o' || c == 'O')
		return (ft_itoa_base((unsigned char)va_arg(args, unsigned int), 8, 0));
	else if (c == 'x' || c == 'X')
		return (ft_itoa_base((unsigned char)va_arg(args, unsigned int), 16,
			c == 'X'));
	else if (c == 'u' || c == 'D')
		return (ft_itoa_base((unsigned char)(va_arg(args, unsigned int)),
			10, 0));
	else if (c == 'U')
		return (ft_itoa_base((va_arg(args, unsigned long)), 10, 0));
	else if (c == 'p')
		return (ft_strjoin_pf("0x", ft_itoa_base(va_arg(args, unsigned long),
			16, 0)));
	else
		return (ft_chartostr(c));
}

char	*choose_conversion(t_flags *flags, const char *str, va_list args)
{
	if (flags->double_h)
		return (conversion_hh(str, args));
	else if (flags->one_h)
		return (conversion_h(str, args));
	else if (flags->one_z)
		return (conversion_z(str, args));
	else if (flags->one_j)
		return (conversion_j(str, args));
	else if (flags->double_l)
		return (conversion_ll(str, args));
	else if (flags->one_l)
		return (conversion_l(str, args));
	else
		return (conversion(str, args));
}
