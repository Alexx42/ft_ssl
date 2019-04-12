/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 20:15:50 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/12 13:39:24 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

#define SHR(x, n) (x >> n)
#define ROTR(x, n) (SHR(x, n) | (x << (64 - n)))

#define O0(x) (ROTR(x, 1) ^ ROTR(x, 8) ^ SHR(x, 7))
#define O1(x) (ROTR(x, 19) ^ ROTR(x, 61) ^ SHR(x, 6))

#define E0(x) (ROTR(x, 28) ^ ROTR(x, 34) ^ ROTR(x, 39))
#define E1(x) (ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41))

#define CH(x, y, z) ((x & y) | (z & (x | y)))
#define MAJ(x, y, z) (z ^ (x & (y ^ z)))

uint64_t g_k512[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538,
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f,
	0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4,
	0x76f988da831153b5, 0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2,
	0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
	0x53380d139d95b3df, 0x650a73548baf63de,
	0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791,
	0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63,
	0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
	0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c,
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84,
	0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

uint64_t g_h512[8] = {
	0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b,
	0xa54ff53a5f1d36f1, 0x510e527fade682d1, 0x9b05688c2b3e6c1f,
	0x1f83d9abfb41bd6b, 0x5be0cd19137e2179};

uint64_t			max_size64(uint64_t n)
{
	uint64_t	x;

	x = 128;
	while (n > (x - 8))
		x += 128;
	return (x);
}

uint64_t		padding_sha512(t_sha512 **sha512, char *content, uint64_t len_content)
{
	int 			bits_len;
	uint64_t		new_len;
	uint64_t		len;

	new_len = len_content * 8 + 1;
	len = len_content;
	bits_len = len_content * 8;
	while (new_len % 1024 != 896)
		new_len++;
	new_len /= 8;
	*sha512 = init_sha512(new_len);
	ft_memcpy((*sha512)->message, content, len_content);
	(*sha512)->message[len_content] = 0x80;
	while (++len < new_len)
		(*sha512)->message[len] = 0;
	bits_len = swap_endian(bits_len);
	ft_memcpy((*sha512)->message + new_len, &bits_len, 8);
	return (new_len);
}

uint64_t	*get_w512(unsigned char *content)
{
	uint64_t		*w;
	size_t			i;
	int		four;

	i = 0;
	four = 0;
	w = (uint64_t*)malloc(sizeof(uint64_t) * 64);
	if (w == NULL)
		return (NULL);
	while (i < 80)
	{
		if (i < 16)
		{
			ft_memcpy(&w[i], content + four, 8);
			w[i] = swap_uint64(w[i]);
			four += 8;
 		}
		else
			w[i] = O1(w[i - 2]) + w[i - 7] + O0(w[i - 15]) + w[i - 16];
		i++;
	}
	return (w);
}

void		main_loop512(int i, t_hash512 **hash512, uint64_t *w)
{
	uint64_t tmp;
	uint64_t tmp2;

	tmp = (*hash512)->h + E1((*hash512)->e) + CH((*hash512)->e,
			(*hash512)->f, (*hash512)->g) + O0(g_k512[i]) + w[i];
	tmp2 = E0((*hash512)->a) + MAJ((*hash512)->a, (*hash512)->b, (*hash512)->c);
	printf("w = %llu \n", w[i]);
	(*hash512)->h = (*hash512)->g;
	(*hash512)->g = (*hash512)->f;
	(*hash512)->f = (*hash512)->e;
	(*hash512)->e = (*hash512)->d + tmp;
	(*hash512)->d = (*hash512)->c;
	(*hash512)->c = (*hash512)->b;
	(*hash512)->b = (*hash512)->a;
	(*hash512)->a = tmp + tmp2;
}

void		cut_blocks512(t_sha512 *sha512, t_hash512 **hash512, size_t new_len)
{
	uint64_t		offset;
	uint64_t	*w;
	int			i;

	offset = 0;
	w = NULL;
	while (offset < new_len)
	{
		i = -1;
		w = get_w512(sha512->message + offset);
		init_hash512(*hash512);
		while (++i < 80)
			main_loop512(i, hash512, w);
		g_h512[0] += (*hash512)->a;
		g_h512[1] += (*hash512)->b;
		g_h512[2] += (*hash512)->c;
		g_h512[3] += (*hash512)->d;
		g_h512[4] += (*hash512)->e;
		g_h512[5] += (*hash512)->f;
		g_h512[6] += (*hash512)->g;
		g_h512[7] += (*hash512)->h;
		offset += 128;
	}
}

void		sha512_hash(t_ssl *ssl)
{
	t_lst		*lst;
	t_sha512	*sha512;
	t_hash512	*hash512;
	uint64_t		newlen;

	lst = ssl->lst;
	hash512 = (t_hash512*)malloc(sizeof(t_hash512));
	while (lst)
	{
		newlen = padding_sha512(&sha512, lst->content, lst->len);
		g_h512[0] = 0x6a09e667f3bcc908;
		g_h512[1] = 0xbb67ae8584caa73b;
		g_h512[2] = 0x3c6ef372fe94f82b;
		g_h512[3] = 0xa54ff53a5f1d36f1;
		g_h512[4] = 0x510e527fade682d1;
		g_h512[5] = 0x9b05688c2b3e6c1f;
		g_h512[6] = 0x1f83d9abfb41bd6b;
		g_h512[7] = 0x5be0cd19137e2179;
		cut_blocks512(sha512, &hash512, newlen);
		print_func(lst, ssl);
		lst = lst->next;
	}
}
