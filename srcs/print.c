/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:23:59 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/07 10:19:54 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

int					is_flags_activated(t_flags *flag, t_lst *lst)
{
	if (!flag->p && !flag->q && !flag->r && !flag->s && !lst->is_string)
		return (1);
	return (0);
}

void				swap_print_md5(t_hash *hash, int status)
{
	hash->h0 = swap_endian(hash->h0);
	hash->h1 = swap_endian(hash->h1);
	hash->h2 = swap_endian(hash->h2);
	hash->h3 = swap_endian(hash->h3);
	ft_printf("%08x", hash->h0);
	ft_printf("%08x", hash->h1);
	ft_printf("%08x", hash->h2);
	ft_printf("%08x", hash->h3);
	if (status)
		ft_putchar('\n');
}

void				print_sha(t_hash256 *hash256, int status)
{
	ft_printf("%08x", hash256->h0);
	ft_printf("%08x", hash256->h1);
	ft_printf("%08x", hash256->h2);
	ft_printf("%08x", hash256->h3);
	ft_printf("%08x", hash256->h4);
	ft_printf("%08x", hash256->h5);
	ft_printf("%08x", hash256->h6);
	ft_printf("%08x", hash256->h7);
	if (status)
		ft_putchar('\n');
}

void				no_flag(t_lst *lst, t_hash *hash, t_hash256 *hash256,
					t_ssl *ssl)
{
	if (lst->name_file)
	{
		ssl->type == 0 ? ft_printf("MD5 (%s) = ", lst->name_file) :
			ft_printf("SHA256 (%s) = ", lst->name_file);
		ssl->type == 0 ? swap_print_md5(hash, 1) : print_sha(hash256, 1);
	}
	else
	{
		if (ssl->type == 0)
		{
			ft_printf("MD5 (\"%s\") = ", lst->content);
			swap_print_md5(hash, 1);
		}
		else
		{
			ft_printf("SHA256 (\"%s\") = ", lst->content);
			print_sha(hash256, 1);
		}
	}
}

void				print_func(t_lst *lst, t_hash *hash, t_hash256 *hash256,
					t_ssl *ssl)
{
	t_flags		*flags;

	flags = lst->flags;
	if (is_flags_activated(flags, lst))
		ssl->type == 0 ? swap_print_md5(hash, 1) : print_sha(hash256, 1);
	else if (flags->p)
	{
		ft_printf("%s", lst->content);
		ssl->type == 0 ? swap_print_md5(hash, 1) : print_sha(hash256, 1);
		flags->p = 0;
	}
	else if (flags->q)
	{
		ssl->type == 0 ? swap_print_md5(hash, 1) : print_sha(hash256, 1);
	}
	else if (flags->r)
	{
		ssl->type == 0 ? swap_print_md5(hash, 0) : print_sha(hash256, 0);
		if (lst->name_file)
			ft_printf(" %s\n", lst->name_file);
		else
			ft_printf(" %s\n", lst->content);
	}
	else if (lst->is_string)
		no_flag(lst, hash, hash256, ssl);
}
