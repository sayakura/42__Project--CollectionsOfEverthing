/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 22:13:45 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/22 22:13:45 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

# define INT_MAX 2147483647
# define BOOL char
# define FALSE 0
# define TRUE 1

typedef enum	e_status
{
	ERROR,
	VALID
}				t_status;

typedef enum	e_is_visit
{
	NOT_VISITED,
	VISITED
}				t_is_visit;

typedef struct	s_queue
{
	int		max_size;
	int		head;
	int		tail;
	int		*list_array;
	BOOL	is_empty;
}				t_queue;

typedef struct	s_poi
{
	int			x;
	int			y;
}				t_poi;

typedef struct	s_res
{
	t_status	status;
	char		**map;
}				t_res;

typedef struct	s_info
{
	int			wd;
	int			len;
	char		ob;
	char		ety;
	char		pth;
	char		en;
	char		dst;
	t_poi		enp;
	t_poi		ext;
}				t_info;

t_info			g_map_i;
BOOL			**g_visit;
t_poi			**g_prev;
t_queue			g_r;
t_queue			g_c;
t_status		read_fst_line(int fd);
char			**read_map(int fd);
t_res			*parser(int fd);
void			ft_create_dp(int len, int wd);
void			print_map(char **map);
void			prompter(int ans);
void			print_and_free(t_res *res, int ans);
void			init(void);
BOOL			is_dupliacte(void);
int				init_queue(void);
#endif
