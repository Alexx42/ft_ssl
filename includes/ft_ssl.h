/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:59:06 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/05 11:58:40 by ale-goff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H
# include <libft.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <unistd.h>

typedef struct		s_hash
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h0;
	uint32_t		h1;
	uint32_t		h2;
	uint32_t		h3;

}					t_hash;

typedef struct		s_hash256
{
	unsigned int		h0;
	unsigned int		h1;
	unsigned int		h2;
	unsigned int		h3;
	unsigned int		h4;
	unsigned int		h5;
	unsigned int		h6;
	unsigned int		h7;
	unsigned int		a;
	unsigned int		b;
	unsigned int		c;
	unsigned int		d;
	unsigned int		e;
	unsigned int		f;
	unsigned int		g;
	unsigned int		h;
}					t_hash256;

typedef struct		s_lst
{
	char			*content;
	char			type;
	size_t			len;
	char			*name_file;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_ssl
{
	t_lst			*lst;
	char			type;
	char			file;
}					t_ssl;

typedef struct		s_flags
{
	char			p;
	char			q;
	char			r;
	char			s;
	char			nb_flags;
	char			space;
}					t_flags;

typedef struct		s_md5
{
	unsigned char	*message;
	size_t			len_message;
}					t_md5;

typedef struct		s_sha256
{
	unsigned char	*message;
	size_t			len_message;
}					t_sha256;

/*
** ERROR
*/

void				wrong_command(char *str);
void				usage(void);
int					verify_cmd(t_ssl *ssl, char *cmd);
void				error_flags(char *str);
int					error_file(int fd, char *str);

/*
** STRUCT
*/

t_ssl				*init_ssl(void);
void				append(t_lst **head, char *content, char type, char *name_file);
t_md5				*init_md5(int len);
void				init_hash256(t_hash256 *hash256);
t_sha256			*init_sha(int len);

/*
** PARSING
*/

int					parsing(char **av, t_ssl *ssl, t_flags *flags);
int					parsing_stdin(t_lst **ssl);

/*
** FLAGS
*/

t_flags				*init_flags();
int					parse_flags(t_flags *flags, char **av);

/*
** PRINTING FUNC
*/

void				print_infos(t_ssl *ssl);
void				print_flags(t_flags *flags);

/*
** ALGO
*/

void				md5_hash(t_flags *flags, t_ssl *ssl);
void				sha256_hash(t_flags *flags, t_ssl *ssl);

/*
** PRINTING FUNCTIONS
*/

void				print_func(t_lst *lst, t_hash *hash, t_flags *flags);
void				print_func_sha(t_lst *lst, t_hash256 *hash, t_flags *flags);

#endif
