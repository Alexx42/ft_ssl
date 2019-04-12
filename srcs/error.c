/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:52:21 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/11 20:22:57 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>

int			verify_cmd(t_ssl *ssl, char *cmd)
{
	if (!ft_strcmp(cmd, "md5"))
	{
		ssl->type = 0;
		return (0);
	}
	else if (!ft_strcmp(cmd, "sha256"))
	{
		ssl->type = 1;
		return (0);
	}
	else if (!ft_strcmp(cmd, "sha512"))
	{
		ssl->type = 2;
		return (0);
	}
	return (1);
}

void		usage(void)
{
	ft_putendl("usage: ft_ssl command [command opts] [command args]");
}

void		wrong_command(char *str)
{
	ft_putstr("\nft_ssl: Error: '");
	ft_putstr(str);
	ft_putstr("' is not a valid command\n");
	ft_putstr("Valid Commands: \n");
	ft_putstr("- md5\n");
	ft_putstr("- sha256\n\n");
	exit(1);
}

void		error_flags(char *str)
{
	ft_putstr("unknown option '");
	ft_putstr(str);
	ft_putstr("'\n");
	ft_putendl("option are");
	ft_putendl("-p, echo STDIN to STDOUT and append the checksum to STDOUT");
	ft_putendl("-q, quiet mode");
	ft_putendl("-r, reverse the format of the output.");
	ft_putendl("-s, print the sum of the given string");
}

int			error_file(int fd, char *str)
{
	if (fd < 0)
	{
		ft_putstr("ft_ssl: ");
		ft_putstr(str);
		ft_putendl(": No such file or directory");
		return (1);
	}
	return (0);
}
