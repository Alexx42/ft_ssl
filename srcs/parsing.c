/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex <Alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:29 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/08 17:06:30 by Alex             ###   ########.fr       */
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
		ft_strdel(&data);
		len = 0;
	}
	ft_strdel(&data);
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
	flags->stop = 1;
	fd = open(str, O_RDONLY);
	if (error_file(fd, str))
		return ;
	data = (char *)ft_strnew(BUFFER);
	while ((len = read(fd, data, sizeof(data))) > 0)
	{
		if (add == NULL)
			add = ft_strdup(data);
		else
			add = join_leak(add, data);
		ft_strdel(&data);
		len = 0;
	}
	close(fd);
	free(data);
	append(lst, add, str, flags);
	ft_strdel(&add);
}

int			op_only(char **av, t_flags **flags)
{
	int i;

	i = 2;
	while (av[i])
	{
		if (av[i][0] == '-' && av[i][1] == 's' && !av[i + 1])
		{
			ft_printf("ft_ssl : -s : need an argument\n");
			exit(1);
		}
		if (av[i][0] == '-' && av[i][1] == 'p')
			(*flags)->p = 1;
		if (av[i][0] != '-')
			return (0);
		i++;
	}
	return (1);
}

int			parsing(int ac, char **av, t_ssl *ssl)
{
	int		i;
	t_flags *flags;

	i = 1;
	flags = init_flags();
	if (ac == 2 || op_only(av, &flags))
		parsing_stdin(&ssl->lst, flags);
	else
		parse_flags(flags, &ssl->lst, av);
	free(flags);
	return (0);
}
