/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 23:45:55 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 10:45:40 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strdup_pf(const char *s1)
{
	char	*cpy;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s1 == NULL)
		return (ft_strdup_pf("(null)"));
	while (s1[i])
		i++;
	if (!(cpy = malloc(sizeof(char) * i + 20)))
		return (NULL);
	while (s1[j])
	{
		cpy[j] = s1[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

char	*ft_strdup_wchar(wchar_t *s1)
{
	char	*cpy;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s1 == NULL)
		return (ft_strdup_pf("(null)"));
	while (s1[i])
		i++;
	if (!(cpy = malloc(sizeof(char) * i + 25)))
		return (NULL);
	while (s1[j])
	{
		cpy[j] = (char)s1[j];
		j++;
	}
	cpy[j] = '\0';
	return (cpy);
}

char	*ft_strjoin_pf(char const *s1, char const *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = (char*)malloc(sizeof(char) * ft_strlen_pf(s1) + ft_strlen_pf(s2) + 1);
	if (new == NULL)
		return (NULL);
	ft_strcpy_pf(new, s1);
	ft_strcat_pf(new, s2);
	free((void *)s2);
	return (new);
}

char	*ft_strcat_pf(char *dest, const char *src)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

size_t	ft_strlen_pf(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
