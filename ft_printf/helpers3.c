/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:46:53 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 10:48:01 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strcpy_pf(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int		ft_putstr_pf(const char *str)
{
	int i;

	i = -1;
	if (str == NULL)
	{
		ft_putstr_pf("(null)");
		return (6);
	}
	while (str[++i])
		write(1, &str[i], 1);
	return (i);
}

void	ft_strdel_pf(char **as)
{
	if (as && *as)
	{
		free(*as);
		*as = NULL;
	}
}
