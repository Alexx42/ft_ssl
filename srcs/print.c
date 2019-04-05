/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:23:59 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/05 10:44:54 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void				swap_print_md5(t_hash *hash)
{
	hash->h0 = swap_endian(hash->h0);
	hash->h1 = swap_endian(hash->h1);
	hash->h2 = swap_endian(hash->h2);
	hash->h3 = swap_endian(hash->h3);
	ft_printf("%02x", hash->h0);
	ft_printf("%02x", hash->h1);
	ft_printf("%02x", hash->h2);
	ft_printf("%02x\n", hash->h3);
}

void				print_func(t_lst *lst, t_hash *hash, t_flags *flags)
{
	if (flags->q == 0 && flags->p == 0)
	{
		if (lst->name_file)
			ft_printf("MD5 (\"%s\") = ", lst->name_file);
		else
			ft_printf("MD5 (\"%s\") = ", lst->content);
		swap_print_md5(hash);
	}
	else if (flags->p)
	{
		ft_printf("%s", lst->content ? lst->content : lst->name_file);
		swap_print_md5(hash);
		flags->p = 0;
	}
	else if (flags->r)
	{
		swap_print_md5(hash);
		ft_printf(" %s\n", lst->content ? lst->content : lst->name_file);
	}
	else
		swap_print_md5(hash);
}

void				print_sha(t_hash256 *hash256)
{
	ft_printf("%02x", hash256->h0);
	ft_printf("%02x", hash256->h1);
	ft_printf("%02x", hash256->h2);
	ft_printf("%02x", hash256->h3);
	ft_printf("%02x", hash256->h4);
	ft_printf("%02x", hash256->h5);
	ft_printf("%02x", hash256->h6);
	ft_printf("%02x\n", hash256->h7);
}

void				print_func_sha(t_lst *lst, t_hash256 *hash, t_flags *flags)
{
	if (flags->q == 0 && flags->p == 0)
	{
		ft_printf("SHA256 (\"%s\") = ", lst->content);
		print_sha(hash);
	}
	else if (flags->p)
	{
		ft_printf("%s", lst->content);
		print_sha(hash);
		flags->p = 0;
	}
	else if (flags->r)
	{
		print_sha(hash);
		ft_printf(" %s\n", lst->content);
	}
	else
		print_sha(hash);
}
