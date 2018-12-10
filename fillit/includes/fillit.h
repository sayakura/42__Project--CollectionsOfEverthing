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
# include <stdint.h>

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
	char			**map;
	unsigned short	length;
	unsigned short	width;
	uint32_t		filled;
}				t_mino;

#define ABS(a) (a < 0 ? -a : a)
#define CHECKNL(c) (c == '\0' || c == '\n')

t_poi			***save_tetriminos(char *buf, short blocks);
int				validate_tetriminos(t_mino *mino);
char			*reader(int fd);

#endif
