/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:15:07 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 16:08:18 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void		init_hash256(t_hash256 *hash256)
{
	hash256->h0 = 0x6A09E667;
	hash256->h1 = 0xbb67ae85;
	hash256->h2 = 0x3c6ef372;
	hash256->h3 = 0xa54ff53a;
	hash256->h4 = 0x510e527f;
	hash256->h5 = 0x9b05688c;
	hash256->h6 = 0x1f83d9ab;
	hash256->h7 = 0x5be0cd19;
	hash256->a = hash256->h0;
	hash256->b = hash256->h1;
	hash256->c = hash256->h2;
	hash256->d = hash256->h3;
	hash256->e = hash256->h4;
	hash256->f = hash256->h5;
	hash256->g = hash256->h6;
	hash256->h = hash256->h7;
}

t_sha256	*init_sha(int len)
{
	t_sha256	*sha256;

	sha256 = (t_sha256 *)malloc(sizeof(t_sha256));
	if (sha256 == NULL)
		return (NULL);
	sha256->message = (unsigned char *)ft_strnew(len + 64);
	return (sha256);
}
