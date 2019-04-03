/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:56 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/02 14:50:21 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

t_lst		*init_lst(void)
{
	t_lst		*list;

	list = (t_lst*)ft_memalloc(sizeof(t_lst));
	if (list == NULL)
		return (NULL);
	list->content = NULL;
	list->type = 0;
	list->next = NULL;
	list->len = 0;
	return (list);
}

void		append(t_lst **head, char *content, char type)
{
	t_lst		*new_node;
	t_lst		*last;

	last = (*head);
	new_node = (t_lst*)malloc(sizeof(t_lst));
	if (new_node == NULL)
		return ;
	new_node->content = ft_strdup(content);
	new_node->type = type;
	new_node->next = NULL;
	new_node->len = ft_strlen(content);
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

t_flags		*init_flags(void)
{
	t_flags		*flags;

	flags = (t_flags*)malloc(sizeof(t_flags));
	if (flags == NULL)
		return (NULL);
	flags->r = 0;
	flags->p = 0;
	flags->q = 0;
	flags->s = 0;
	flags->space = 0;
	flags->nb_flags = 0;
	return (flags);
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
		// if (lst->content != NULL)
			printf("CONTENT = %s\n", lst->content);
		lst = lst->next;
	}
}

void		print_flags(t_flags *flags)
{
	printf("R = %d\n", flags->r);
	printf("P = %d\n", flags->p);
	printf("Q = %d\n", flags->q);
	printf("S = %d\n", flags->s);
	printf("Number of args: %d\n", flags->nb_flags);
}
