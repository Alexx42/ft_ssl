/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_blocks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 16:33:36 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 09:56:30 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

/*
** The values of g_r correponds to the number of shift
** that we need to do depending on the round
*/

int32_t g_r[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21,
	6, 10, 15, 21, 6, 10, 15, 21};

/*
** The values of k corresponds to the constant of the algorithm
** using binary integer part of the sines of integers
*/

int32_t g_k[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

/*
** Variables for the algorithm
*/

uint32_t g_h[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};

uint32_t g_w[16] = {0};

t_hash	*init_hash(void)
{
	t_hash	*hash;

	hash = (t_hash*)malloc(sizeof(t_hash));
	if (hash == NULL)
		return (NULL);
	hash->a = g_h[0];
	hash->b = g_h[1];
	hash->c = g_h[2];
	hash->d = g_h[3];
	hash->f = 0;
	hash->g = 0;
	return (hash);
}

void	main_loop(t_hash *hash, uint32_t *w, int i)
{
	if (i <= 15)
	{
		hash->f = f_func(hash->b, hash->c, hash->d);
		hash->g = i;
	}
	else if (i <= 31)
	{
		hash->f = g_func(hash->b, hash->c, hash->d);
		hash->g = (5 * i + 1) % 16;
	}
	else if (i <= 47)
	{
		hash->f = h_func(hash->b, hash->c, hash->d);
		hash->g = (3 * i + 5) % 16;
	}
	else
	{
		hash->f = i_func(hash->b, hash->c, hash->d);
		hash->g = (7 * i) % 16;
	}
	hash->f = hash->f + hash->a + g_k[i] + w[hash->g];
	hash->a = hash->d;
	hash->d = hash->c;
	hash->c = hash->b;
	hash->b = hash->b + (ROTATE_LEFT(hash->f, g_r[i]));
}

void	cut_blocks(t_md5 *md5, int new_len)
{
	t_hash			*hash;
	int				offset;
	uint32_t		*w;
	uint32_t		i;

	offset = 0;
	while (offset < new_len)
	{
		w = (uint32_t*)(md5->message + offset);
		hash = init_hash();
		i = -1;
		while (++i < 64)
			main_loop(hash, w, i);
		g_h[0] += hash->a;
		g_h[1] += hash->b;
		g_h[2] += hash->c;
		g_h[3] += hash->d;
		offset += 64;
	}
	i = -1;
	while (++i < 4)
		g_h[i] = swap_endian(g_h[i]);
}
