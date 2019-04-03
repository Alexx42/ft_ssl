/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-goff <ale-goff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 19:59:06 by ale-goff          #+#    #+#             */
/*   Updated: 2019/04/03 12:32:09 by ale-goff         ###   ########.fr       */
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
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

typedef struct		s_hash
{
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
}					t_hash;

typedef struct		s_lst
{
	char			*content;
	char			type;
	size_t			len;
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
	uint32_t		*w;
}					t_md5;

/*
** ERROR
*/

void				wrong_command(char *str);
void				usage(void);
int					verify_cmd(t_ssl *ssl, char *cmd);
void				error_flags(char *str);

/*
** STRUCT
*/

t_ssl				*init_ssl(void);
void				append(t_lst **head, char *content, char type);

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
** NON LINEAR FUNC
*/

uint32_t					f_func(int b, int c, int d);
uint32_t					g_func(int b, int c, int d);
uint32_t					h_func(int b, int c, int d);
uint32_t					i_func(int b, int c, int d);

/*
** PADDING
*/

void				padding(t_md5 *md5, t_lst *lst, int new_len);


/*
** CUTTING BLOCKS
*/

void				cut_blocks(t_md5 *md5, t_ssl *ssl, int new_len);

#endif
