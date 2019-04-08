/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:49 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/05 21:31:28 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

void 			error_sflags()
{
	ft_printf("ft_ssl: -s : need an argument");
	exit (1);
}

int 			parse_string(t_lst **lst, char **str, t_flags *flags, int i)
{
	(void)lst;
	(void)flags;
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

void			parse_flags(t_flags *flags, t_lst **lst, char **str)
{
	int			i;
	int			j;

	i = -1;
	while (str[++i])
	{
		printf("SALUT\n");
		j = -1;
		if (str[i][0] == '-' && !flags->stop)
		{
			while (str[i][++j])
			{

					if (str[i][j] == 's')
					{
						i = parse_string(lst, str, flags, i);
						break ;
					}
					if (str[i][j] == 'p')
					{
						print_flags(flags);
						(flags)->p = 1;
						parsing_stdin(lst, flags);
					}
					if (str[i][j] == 'q')
						flags->q = 1;
					if (str[i][j] == 'r')
						flags->r = 1;
				}
		}
		// else
		// {
		// 	append_file(lst, str[i], flags);
		// 	i++;
		// }
	}
}
