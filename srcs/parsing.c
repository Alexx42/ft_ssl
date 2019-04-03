/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:29 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/03 09:53:03 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = (char*)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (new == NULL)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcat(new, s2);
	// free((void *)s2);
	return (new);
}

int			parsing_stdin(t_lst *list)
{
	char		*str;
	char		data[128] = {0};
	int			i = 0;
	str = NULL;
	while (read(0, data, sizeof(data)) > 0)
	{
		if (str == NULL)
			str  = ft_strdup(data);
		else
			str = ft_strjoin(str, data);
		i++;
	}
	if (str != NULL)
		append(&list, str, 0);
	ft_strdel(&str);
	return (0);
}

void		append_file(t_lst **lst, char *str)
{
	int		fd;
	char	*line;
	char	*add;

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
			add = ft_strjoin(add, line);
		ft_strdel(&line);
	}
	append(lst, add, 0);
	ft_strdel(&add);
}

int			parsing(char **av, t_ssl *ssl, t_flags *flag)
{
	int		i;

	i = 2 + flag->nb_flags - flag->space;
	if (!isatty(0))
		parsing_stdin(ssl->lst);
	while (av[i])
	{
		if (flag->s)
		{
			append(&ssl->lst, flag->space ? &av[i][2] : av[i], 1);
			flag->s = 0;
		}
		else
			append_file(&ssl->lst, av[i]);
		
		i++;
	}
	return (0);
}
