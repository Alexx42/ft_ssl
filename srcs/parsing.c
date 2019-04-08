/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:29 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/05 21:37:07 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

#define BUFFER 4096

char		*join_leak(char *add, char *data)
{
	char		*tmp;

	tmp = ft_strjoin(add, data);
	free(add);
	return (tmp);
}

int			parsing_stdin(t_lst **list, t_flags *flags)
{
	char				*str;
	char				*data;
	int					len;

	str = NULL;
	data = (char *)ft_strnew(BUFFER);
	while ((len = read(0, data, sizeof(data))) > 0)
	{
		if (str == NULL)
			str = ft_strdup(data);
		else
			str = join_leak(str, data);
		ft_bzero(data, len);
		len = 0;
	}
	if (str != NULL)
		append(list, str, NULL, flags);
	ft_strdel(&str);
	return (0);
}

void		append_file(t_lst **lst, char *str, t_flags *flags)
{
	int		fd;
	char	*data;
	char	*add;
	int		len;

	add = NULL;
	data = (char *)ft_strnew(BUFFER);
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
	append(lst, add, str, flags);
	ft_strdel(&add);
}

int			parsing(int ac, char **av, t_ssl *ssl)
{
	int		i;
	t_flags *flags;

	i = 1;
	flags = init_flags();
	if (ac == 2)
		parsing_stdin(&ssl->lst, flags);
	else
	{
		parse_flags(flags, &ssl->lst, av);
		print_infos(ssl);
	}
	return (0);
}
