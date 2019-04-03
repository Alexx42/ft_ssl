/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:35 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/03 11:09:50 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>


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

void		md5_hash(t_flags *flags, t_ssl *ssl)
{
	t_md5		*md5;
	int			new_len;

	(void)flags;
	new_len = ssl->lst->len * 8 + 1;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
 	md5 = init_md5(new_len);
	padding(md5, ssl->lst, new_len);
	cut_blocks(md5, ssl, new_len);
}
