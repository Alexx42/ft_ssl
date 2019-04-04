/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:35 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/04 09:49:10 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>


void		md5_hash(t_flags *flags, t_ssl *ssl)
{
	t_md5		*md5;
	uint32_t			new_len;

	(void)flags;
	md5 = NULL;
	new_len = padding(&md5, ssl->lst);
	cut_blocks(md5, new_len);
}
