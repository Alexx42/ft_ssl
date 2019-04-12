/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:15:07 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/12 11:19:21 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

extern unsigned int g_h256[8];
extern uint64_t		g_h512[8];

void				init_hash256(t_hash256 *hash256)
{
	hash256->a = g_h256[0];
	hash256->b = g_h256[1];
	hash256->c = g_h256[2];
	hash256->d = g_h256[3];
	hash256->e = g_h256[4];
	hash256->f = g_h256[5];
	hash256->g = g_h256[6];
	hash256->h = g_h256[7];
}

t_sha256			*init_sha(int len)
{
	t_sha256	*sha256;

	sha256 = (t_sha256 *)malloc(sizeof(t_sha256));
	if (sha256 == NULL)
		return (NULL);
	sha256->message = (unsigned char *)ft_strnew(len + 128);
	return (sha256);
}

int					is_flags_activated(t_flags *flag, t_lst *lst)
{
	if (!flag->p && !flag->q && !flag->r && !flag->s && !lst->is_string)
		return (1);
	return (0);
}

t_sha512			*init_sha512(int newlen)
{
	t_sha512	*sha;

	if ((sha = (t_sha512*)malloc(sizeof(t_sha512))) == NULL)
		return (NULL);
	sha->message = (unsigned char*)ft_strnew(newlen + 64);
	return (sha);
}

void				init_hash512(t_hash512 *hash)
{
	hash->a = g_h512[0];
	hash->b = g_h512[1];
	hash->c = g_h512[2];
	hash->d = g_h512[3];
	hash->e = g_h512[4];
	hash->f = g_h512[5];
	hash->g = g_h512[6];
	hash->h = g_h512[7];
}
