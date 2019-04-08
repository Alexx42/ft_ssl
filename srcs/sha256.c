/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:39 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/05 13:42:38 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define SHR(x, n) ((x) >> n)
#define E0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define E1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define O0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define O1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))

uint64_t g_ksha[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

size_t			padding_sha256(t_sha256 **sha256, char *content,
				int len_content)
{
	uint64_t	bits_len;
	size_t		new_len;
	size_t		len;

	bits_len = len_content * 8;
	new_len = len_content * 8 + 1;
	len = len_content;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	*sha256 = init_sha(new_len);
	ft_memcpy((*sha256)->message, content, len_content);
	(*sha256)->message[len_content] = 0x80;
	while (++len <= new_len)
		(*sha256)->message[len] = 0;
	bits_len = swap_uint64(bits_len);
	ft_memcpy((*sha256)->message + new_len, &bits_len, 8);
	return (new_len);
}

unsigned int	*get_w(unsigned char *w_offset)
{
	unsigned int	*w;
	size_t			i;

	i = 0;
	w = (unsigned int*)malloc(sizeof(unsigned int) * 64);
	if (w == NULL)
		return (NULL);
	while (i < 64)
	{
		if (i < 16)
			w[i] = (w_offset[i * 4] << 24) |
				(w_offset[i * 4 + 1] << 16) |
				(w_offset[i * 4 + 2] << 8) |
				(w_offset[i * 4 + 3]);
		else
			w[i] = w[i - 16] + w[i - 7] + O0(w[i - 15]) + O1(w[i - 2]);
		i++;
	}
	return (w);
}

void			main_loop256(t_hash256 **hash256, size_t i, unsigned int *w)
{
	int	tmp1;
	int	tmp2;

	tmp1 = (*hash256)->h + E1((*hash256)->e) + CH((*hash256)->e,
			(*hash256)->f, (*hash256)->g) + g_ksha[i] + w[i];
	tmp2 = E0((*hash256)->a) + MAJ((*hash256)->a,
			(*hash256)->b, (*hash256)->c);
	(*hash256)->h = (*hash256)->g;
	(*hash256)->g = (*hash256)->f;
	(*hash256)->f = (*hash256)->e;
	(*hash256)->e = (*hash256)->d + tmp1;
	(*hash256)->d = (*hash256)->c;
	(*hash256)->c = (*hash256)->b;
	(*hash256)->b = (*hash256)->a;
	(*hash256)->a = tmp1 + tmp2;
}

void			cut_blocks256(t_sha256 *sha256, t_hash256 **hash256, int newlen)
{
	size_t				offset;
	unsigned int		*w;
	size_t				i;

	offset = 0;
	w = NULL;
	while (offset < (size_t)newlen)
	{
		w = get_w(sha256->message + offset);
		init_hash256(*hash256);
		i = -1;
		while (++i < 64)
			main_loop256(hash256, i, w);
		(*hash256)->h0 += (*hash256)->a;
		(*hash256)->h1 += (*hash256)->b;
		(*hash256)->h2 += (*hash256)->c;
		(*hash256)->h3 += (*hash256)->d;
		(*hash256)->h4 += (*hash256)->e;
		(*hash256)->h5 += (*hash256)->f;
		(*hash256)->h6 += (*hash256)->g;
		(*hash256)->h7 += (*hash256)->h;
		offset += 64;
	}
	free(w);
}

void			sha256_hash(t_ssl *ssl)
{
	t_lst		*lst;
	size_t		newlen;
	t_sha256	*sha256;
	t_hash256	*hash256;

	lst = ssl->lst;
	hash256 = (t_hash256 *)malloc(sizeof(t_hash256));
	while (lst)
	{
		newlen = padding_sha256(&sha256, lst->content, lst->len);
		(hash256)->h0 = 0x6A09E667;
		(hash256)->h1 = 0xbb67ae85;
		(hash256)->h2 = 0x3c6ef372;
		(hash256)->h3 = 0xa54ff53a;
		(hash256)->h4 = 0x510e527f;
		(hash256)->h5 = 0x9b05688c;
		(hash256)->h6 = 0x1f83d9ab;
		(hash256)->h7 = 0x5be0cd19;
		cut_blocks256(sha256, &hash256, newlen);
		print_func(lst, NULL, hash256, ssl);
		free(sha256->message);
		free(sha256);
		lst = lst->next;
	}
	free(hash256);
}
