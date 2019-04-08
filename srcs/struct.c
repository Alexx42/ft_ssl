/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex <Alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:56 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/05 16:15:41 by Alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

t_flags		*init_flags(void)
{
	t_flags		*flags;

	flags = (t_flags*)ft_memalloc(sizeof(t_flags));
	if (flags == NULL)
		return (NULL);
	flags->r = 0;
	flags->p = 0;
	flags->q = 0;
	flags->s = 0;
	flags->space = 0;
	flags->stop = 0;
	return (flags);
}

t_flags		*duplicate_flags(t_flags *cpy)
{
	t_flags		*flags;

	flags = (t_flags*)malloc(sizeof(t_flags));
	flags->p = cpy->p;
	flags->q = cpy->q;
	flags->r = cpy->r;
	flags->s = cpy->r;
	return (flags);
}

void		append(t_lst **head, char *content, char *file_name, t_flags *flags)
{
	t_lst		*new_node;
	t_lst		*last;

	last = (*head);
	new_node = (t_lst*)malloc(sizeof(t_lst));
	if (new_node == NULL)
		return ;
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	new_node->name_file = file_name ? ft_strdup(file_name) : NULL;
	new_node->len = ft_strlen(content);
	new_node->flags = duplicate_flags(flags);
	new_node->is_string = 0;
	if (flags->s)
	{
		new_node->is_string = 1;
		flags->s = 0;
	}
	if (!(*head))
	{
		(*head) = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

t_ssl		*init_ssl(void)
{
	t_ssl		*ssl;

	ssl = (t_ssl*)malloc(sizeof(t_ssl));
	if (ssl == NULL)
		return (NULL);
	ssl->type = 0;
	ssl->lst = NULL;
	ssl->file = 0;
	return (ssl);
}

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


void		print_infos(t_ssl *ssl)
{
	t_lst	*lst;

	lst = ssl->lst;
	printf("INFOS SSL\n");
	if (ssl->type == 1)
		printf("TYPE = MD5\n");
	else
		printf("TYPE = SHA256\n");
	while (lst)
	{
		printf("CONTENT = %s\n", lst->content);
		printf("IS_STRING = %d\n", lst->is_string);
		print_flags(lst->flags);
		lst = lst->next;
	}
}

void		print_flags(t_flags *flags)
{
	printf("R = %d\n", flags->r);
	printf("P = %d\n", flags->p);
	printf("Q = %d\n", flags->q);
	printf("S = %d\n", flags->s);

}
