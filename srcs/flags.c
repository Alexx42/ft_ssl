/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alex <Alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:49 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/09 13:24:06 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void			error_sflags(void)
{
	ft_printf("ft_ssl: -s : need an argument");
	exit(1);
}

int				parse_string(t_lst **lst, char **str, t_flags *flags, int i)
{
	if (!str[i + 1])
		error_sflags();
	else
	{
		flags->s = 1;
		i += 1;
		append(lst, str[i], NULL, flags);
	}
	return (i);
}

void			parse_flags2(t_flags *flags, char **str, int i, t_lst **lst)
{
	int		j;

	j = -1;
	while (str[i][++j])
	{
		if (str[i][j] == 's')
		{
			i = parse_string(lst, str, flags, i);
			break ;
		}
		if (str[i][j] == 'p')
		{
			(flags)->p = 1;
			parsing_stdin(lst, flags);
			flags->p = 0;
		}
		str[i][j] == 'q' ? flags->q = 1 : 0;
		str[i][j] == 'r' ? flags->r = 1 : 0;
	}
}

void			parse_flags(t_flags *flags, t_lst **lst, char **str)
{
	int			i;

	i = 1;
	while (str[++i])
	{
		if (str[i][0] == '-' && !flags->stop)
		{
			parse_flags2(flags, str, i, lst);
		}
		else
		{
			append_file(lst, str[i], flags);
		}
	}
}
