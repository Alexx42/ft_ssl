/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:49 by ale-goff          #+#    #+#             */
/*   Updated: 2019/03/31 20:03:31 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void		parse_flags3(t_flags *flags, int i, char **av)
{
	if (av[i][2])
		flags->space = 1;
	flags->s = 1;
}

int			parse_flags2(t_flags *flags, int i, char **av)
{
	int		ret;

	ret = 0;
	if (av[i][0] == '-')
	{
		ret = 1;
		flags->nb_flags++;
		if (av[i][1] == 'q' && !av[i][2])
			flags->q = 1;
		else if (av[i][1] == 'p' && !av[i][2])
			flags->p = 1;
		else if (av[i][1] == 's')
			parse_flags3(flags, i, av);
		else if (av[i][1] == 'r' && !av[i][2])
			flags->r = 1;
		else
		{
			flags->nb_flags--;
			error_flags(av[i]);
			exit(1);
		}
	}
	return (ret);
}

int			parse_flags(t_flags *flags, char **av)
{
	int		i;
	int		ret;

	i = 2;
	while (av[i])
	{
		if (av[i][0] != '-')
			return (0);
		ret = parse_flags2(flags, i, av);
		if (flags->s)
			return (0);
		i++;
	}
	return (ret);
}
