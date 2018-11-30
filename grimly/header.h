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

# define INT_MAX 2147483647
# define bool char
# define false 0
# define true 1
typedef enum    e_status
{
	ERROR,
	VALID
}               t_status;

typedef enum    e_is_visit
{
	NOT_VISITED,
	VISITED
}               t_is_visit;


typedef struct s_queue
{
	int		maxSize;
	int		head;
	int		tail;
	int		*listArray;
	bool 	isEmpty;
}				t_queue;

typedef struct s_poi
{
	int             x;
	int             y;
}               t_poi;
/*
typedef struct s_path
{
	t_poi   		*head;
	t_poi   		*tail;
}               t_path;
*/

typedef struct s_list
{
	void            *data;
	struct s_list   *next;
}               t_list;

typedef struct s_res
{
	t_status    status;
	char        *map;
}               t_res;

typedef struct  s_info
{
	int     wd;
	int     len;
	char    ob;
	char    ety;
	char    pth;
	char    en;
	char    dst;
	t_poi	enp;
	t_poi	ext;
}               t_info;

t_info  g_map_i;
bool 	**g_visit;
t_poi 	**g_prev;
void    ft_putstr_fd(const char *str, int fd);
void    ft_putchar_fd(char c, int fd);
int		ft_c_at(char *str, int ch);
char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n);
int		ft_atoi(const char *str);
char	*ft_strnew(size_t size);
int		ft_isdigit(char c);
size_t	ft_strlen(const char *str);
void	ft_create_dp(int len, int wd);
t_list 	*ft_new_node(void *data);
void	ft_lst_append(t_list **ref, void *data);
void	ft_putnbr(size_t n);
#endif