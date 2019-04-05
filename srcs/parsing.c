/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:29 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/05 10:46:50 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

int			parsing_stdin(t_lst **list)
{
	char		*str;
	char		data[128];
	int			i;

	str = NULL;
	i = 0;
	while (read(0, data, sizeof(data)) > 0)
	{
		if (str == NULL)
			str = ft_strdup(data);
		else
			str = ft_strjoin(str, data);
		i++;
	}
	if (str != NULL)
		append(list, str, 0, NULL);
	ft_strdel(&str);
	return (0);
}

void		append_file(t_lst **lst, char *str)
{
	int		fd;
	char	*line;
	char	*add;
	char	*tmp;

	add = NULL;
	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("ft_ssl: ");
		ft_putstr(str);
		ft_putendl(": No such file or directory");
		return ;
	}
	while (get_next_line(fd, &line))
	{
		if (add == NULL)
			add = ft_strdup(line);
		else
		{
			tmp = ft_strjoin(add, line);
			free(add);
			add = tmp;
		}
		ft_strdel(&line);
	}
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
