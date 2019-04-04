/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:10:48 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 09:49:02 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

/*
**  PREPARATION OF THE MESSAGE
*/

t_md5		*init_md5(int len)
{
	t_md5	*md5;

	md5 = (t_md5 *)malloc(sizeof(t_md5));
	if (md5 == NULL)
		return (NULL);
	md5->message = (unsigned char *)ft_strnew(len + 64);
	md5->len_message = 0;
	return (md5);
}

uint32_t		padding(t_md5 **md5, t_lst *lst)
{
	uint32_t		new_len;
	uint32_t		len;
	uint32_t		bit_len;

	new_len = lst->len * 8 + 1;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	bit_len = lst->len * 8;
	len = lst->len;
	*md5 = init_md5(new_len);
	ft_memcpy((*md5)->message, lst->content, lst->len);
	(*md5)->message[lst->len] = (char)0x80;
	while (++len <= new_len)
		(*md5)->message[len] = 0;
	ft_memcpy((*md5)->message + new_len, &bit_len, 4);
	return (new_len);
}
