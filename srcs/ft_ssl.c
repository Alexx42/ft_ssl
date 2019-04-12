/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:12 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/12 10:39:53 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

t_hashing	g_hash[] = {md5_hash, sha256_hash, sha512_hash};

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
	if (verify_cmd(ssl, av[0]))
		wrong_command(av[0]);
	parsing(ac, av, ssl);
	g_hash[(int)ssl->type](ssl);
	free_list(ssl->lst);
	free(ssl);
	return (0);
}

int		main(int ac, char **av)
{
	char		**split;
	char		*line;

	if (ac == 1)
	{
		get_next_line(0, &line);
		split = ft_strsplit(line, ' ');
		ft_strdel(&line);
		ft_ssl(split, ac);
		free(split);
	}
	else
		ft_ssl(av + 1, ac);
	return (0);
}
