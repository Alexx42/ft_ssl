/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex <Alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:12 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/09 13:09:12 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

t_hashing	g_hash[] = {md5_hash, sha256_hash};

void	free_list(t_lst *head)
{
	t_lst *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->flags)
			free(tmp->flags);
		if (tmp->content)
			free(tmp->content);
		if (tmp->name_file)
			free(tmp->name_file);
		free(tmp);
	}
}

int		ft_ssl(char **av, int ac)
{
	t_ssl		*ssl;

	ssl = init_ssl();
	if (verify_cmd(ssl, av[1]))
		wrong_command(av[1]);
	parsing(ac, av, ssl);
	g_hash[(int)ssl->type](ssl);
	free_list(ssl->lst);
	free(ssl);
	return (0);
}

int		main(int ac, char **av)
{
	if (ac == 1)
		usage();
	else
		ft_ssl(av, ac);
	return (0);
}
