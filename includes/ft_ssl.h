/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:59:06 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/07 10:21:05 by ale-goff         ###   ########.fr       */
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

typedef struct		s_flags
{
	char			p;
	char			q;
	char			r;
	char			s;
	char			space;
	char			stop;
}					t_flags;

typedef struct		s_lst
{
	char			*content;
	size_t			len;
	char			*name_file;
	t_flags			*flags;
	char			is_string;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_ssl
{
	t_lst			*lst;
	char			type;
	char			file;
}					t_ssl;

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

typedef void		(*t_hashing)(t_ssl *ssl);

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
void				append(t_lst **head, char *content, char *file_name,
					t_flags *flags);
void				append_file(t_lst **lst, char *str, t_flags *flags);
t_md5				*init_md5(int len);
void				init_hash256(t_hash256 *hash256);
t_sha256			*init_sha(int len);

/*
** PARSING
*/

int					parsing(int ac, char **av, t_ssl *ssl);
int					parsing_stdin(t_lst **list, t_flags *flags);

/*
** FLAGS
*/

t_flags				*init_flags();
void				parse_flags(t_flags *flags, t_lst **lst, char **av);

/*
** PRINTING FUNC
*/

void				print_infos(t_ssl *ssl);
void				print_flags(t_flags *flags);

/*
** ALGO
*/

void				md5_hash(t_ssl *ssl);
void				sha256_hash(t_ssl *ssl);

/*
** PRINTING FUNCTIONS
*/

void				print_func(t_lst *lst, t_hash *hash, t_hash256 *hash256,
					t_ssl *ssl);
void				print_sha(t_hash256 *hash256, int status);
void				swap_print_md5(t_hash *hash, int status);

#endif
