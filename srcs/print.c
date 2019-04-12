/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:23:59 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/12 11:06:36 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

extern uint32_t g_h[4];
extern unsigned int g_h256[8];
extern uint64_t		g_h512[8];
t_print		g_print[] = {swap_print_md5, print_sha, print_sha512};

void				swap_print_md5(int status)
{
	g_h[0] = swap_endian(g_h[0]);
	g_h[1] = swap_endian(g_h[1]);
	g_h[2] = swap_endian(g_h[2]);
	g_h[3] = swap_endian(g_h[3]);
	ft_printf("%08x", g_h[0]);
	ft_printf("%08x", g_h[1]);
	ft_printf("%08x", g_h[2]);
	ft_printf("%08x", g_h[3]);
	if (status)
		ft_putchar('\n');
}

void				print_sha512(int status)
{
	printf("%08llx", g_h512[0]);
	printf("%08llx", g_h512[1]);
	printf("%08llx", g_h512[2]);
	printf("%08llx", g_h512[3]);
	printf("%08llx", g_h512[4]);
	printf("%08llx", g_h512[5]);
	printf("%08llx", g_h512[6]);
	printf("%08llx", g_h512[7]);
	if (status)
		ft_putchar('\n');
}

void				print_sha(int status)
{
	ft_printf("%08x", g_h256[0]);
	ft_printf("%08x", g_h256[1]);
	ft_printf("%08x", g_h256[2]);
	ft_printf("%08x", g_h256[3]);
	ft_printf("%08x", g_h256[4]);
	ft_printf("%08x", g_h256[5]);
	ft_printf("%08x", g_h256[6]);
	ft_printf("%08x", g_h256[7]);
	if (status)
		ft_putchar('\n');
}

void				no_flag(t_lst *lst, t_ssl *ssl)
{
	if (lst->name_file)
	{
		if (ssl->type == 0)
			ft_printf("MD5 (\"%s\") = ", lst->name_file);
		else if (ssl->type == 1)
			ft_printf("SHA256 (\"%s\") = ", lst->name_file);
		else
			ft_printf("SHA512 (\"%s\") = ", lst->name_file);
	}
	else
	{
		if (ssl->type == 0)
			ft_printf("MD5 (\"%s\") = ", lst->content);
		else if (ssl->type == 1)
			ft_printf("SHA256 (\"%s\") = ", lst->content);
		else
			ft_printf("SHA512 (\"%s\") = ", lst->content);
	}
	g_print[(int)ssl->type](1);
}

void				print_func(t_lst *lst, t_ssl *ssl)
{
	t_flags		*flags;

	flags = lst->flags;
	if (is_flags_activated(flags, lst) && lst->name_file == NULL)
		g_print[(int)ssl->type](1);
	else if (flags->p)
	{
		ft_printf("%s", lst->content);
		g_print[(int)ssl->type](1);
		flags->p = 0;
	}
	else if (flags->q)
	{
		g_print[(int)ssl->type](1);
	}
	else if (flags->r)
	{
		g_print[(int)ssl->type](0);
		lst->name_file ? ft_printf(" %s\n", lst->name_file) :
		ft_printf(" \"%s\"\n", lst->content);
	}
	else if (lst->is_string || lst->name_file != NULL)
		no_flag(lst, ssl);
}
