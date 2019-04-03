/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:10:48 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/03 12:06:43 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

/*
**  PREPARATION OF THE MESSAGE
*/

void		padding(t_md5 *md5, t_lst *lst, int new_len)
{
	int		len;
	uint32_t bit_len;
	
	bit_len = 8 * lst->len;
	len =  lst->len;
	ft_memcpy(md5->message, lst->content, lst->len);
	md5->message[lst->len] = (char)0x80;
	while (++len <= new_len)
		md5->message[len] = 0;
	ft_memcpy(md5->message + new_len , &bit_len, 4);
}

