/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:29 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/05 12:11:33 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

char		*join_leak(char *add, char *data)
{
	char		*tmp;

	tmp = ft_strjoin(add, data);
	free(add);
	return (tmp);
}

int			parsing_stdin(t_lst **list)
{
	char		*str;
	char		data[1000];

	str = NULL;
	while (read(0, data, sizeof(data)) > 0)
	{
		if (str == NULL)
			str = ft_strdup(data);
		else
			str = ft_strjoin(str, data);
	}
	if (str != NULL)
		append(list, str, 0, NULL);
	ft_strdel(&str);
	return (0);
}

void		append_file(t_lst **lst, char *str)
{
	int		fd;
	char	*data;
	char	*add;
	int		len;

	add = NULL;
	data = (char *)ft_strnew(10000 + 1);
	fd = open(str, O_RDONLY);
	if (error_file(fd, str))
		return ;
	while ((len = read(fd, data, sizeof(data))) > 0)
	{
		if (add == NULL)
			add = ft_strdup(data);
		else
			add = join_leak(add, data);
		ft_bzero(data, len);
		len = 0;
	}
	close(fd);
	append(lst, add, 1, str);
	ft_strdel(&add);
}

int			parsing(char **av, t_ssl *ssl, t_flags *flag)
{
	int		i;

	i = 2 + flag->nb_flags - flag->space;
	if (flag->p)
		parsing_stdin(&ssl->lst);
	while (av[i])
	{
		if (flag->s)
		{
			append(&ssl->lst, flag->space ? &av[i][2] : av[i], 0, NULL);
			flag->s = 0;
		}
		else
			append_file(&ssl->lst, av[i]);
		i++;
	}
	return (0);
}
