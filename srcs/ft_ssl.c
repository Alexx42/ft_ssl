/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:12 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/05 10:47:55 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void	free_list(t_lst *head)
{
	t_lst *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->content);
		free(tmp);
	}
}

int		ft_ssl(char **av)
{
	t_ssl		*ssl;
	t_flags		*flags;

	ssl = init_ssl();
	flags = init_flags();
	if (verify_cmd(ssl, av[1]))
		wrong_command(av[1]);
	if (!av[2] || parse_flags(flags, av) == 1)
		parsing_stdin(&ssl->lst);
	else
		parsing(av, ssl, flags);
	if (ssl->type == 1)
		md5_hash(flags, ssl);
	else
		sha256_hash(flags, ssl);
	free_list(ssl->lst);
	free(flags);
	free(ssl);
	return (0);
}

int		main(int ac, char **av)
{
	if (ac == 1)
		usage();
	else
		ft_ssl(av);
	return (0);
}
