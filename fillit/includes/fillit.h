/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 05:16:52 by qpeng             #+#    #+#             */
/*   Updated: 2018/11/25 20:38:21 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../libft/libft.h"

typedef enum	status
{
	Invalid,
	Valid
}				t_status;

typedef struct	s_poi
{
	short		x;
	short		y;
}				t_poi;

typedef struct	s_mino{
	t_poi			***minos;
	unsigned char	length;
	unsigned short	width;
}				t_mino;
/*
typedef struct	s_list
{
	t_poi			data;
	struct s_list	next;
}				t_list;*/
//void	solve(char **shapes, int c);

#endif
