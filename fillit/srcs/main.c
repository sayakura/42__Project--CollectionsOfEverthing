/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 05:19:09 by qpeng             #+#    #+#             */
/*   Updated: 2018/11/26 21:06:20 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/fillit.h"
#include "../includes/libft.h"
#include <stdio.h>

/*
** Read the map in to a bufer called buf.
** Ultimate tricky code.
*/
#define ABS(a) (a < 0 ? -a : a)
#define CHECKNL(c) (c == '\0' || c == '\n')

//#define COX(num, index, rx)  ((num - (num + index - (num % 5))) - rx)
//#define COY(num, index, ry)  ((((num / 5) + index) %  5) - ry)

inline static int	ft_sqrt(int n)
{
	int x; 
    int y; 

	x = n;
	y = 1; 
    while(x > y) 
    { 
        x = (x + y) / 2; 
        y = n / x; 
    } 
    return x; 
}

t_poi		*create_point(short	y, short x)
{
	t_poi	*point;

	point = (t_poi *)malloc(sizeof(t_poi));
	point->x = x;
	point->y = y;
	return (point);
}

static t_poi	**save_this_block(char **map)
{
	int 	i;
	int		b_i;
	t_poi	*poi;
	t_poi	**block;

	// for (int i = 0; i < 21; i++)
	// 	printf("%c", (*map)[i]);

	b_i = 0;
	i = 0;
	poi = malloc(sizeof(t_poi));
	block = malloc(sizeof(t_poi *) * 4);
	while ((*map)[i] != '#')
		i++;
	poi->x = (i % 5);
	poi->y = (i / 5);
	//printf("i: [%d], x:%d, y:%d\n", i, poi->x, poi->y);
	block[b_i++] = poi;
	while (++i < 20 && b_i < 4)
	{
		poi = malloc(sizeof(t_poi));
		while ((*map)[i] != '#' && i < 20)
			i++;
		poi->x = (i % 5) - block[0]->x;
		poi->y = (i / 5) - (block[0]->y);
		//printf("i: [%d], x:%d, y:%d\n", i, (i % 5) , (i / 5));
		block[b_i++] = poi;
	}
	*map += 21;
	//printf("==========\n");
	return (block);
}

static t_poi	***save_tetriminos(char *buf, short blocks)
{
	short 	i;
	t_poi 	***minos;

	i = 0;
	minos = (t_poi ***)malloc(sizeof(t_poi**) * blocks);

	// printf("saving all the blocks(total of %d blocks): \n", blocks);
	while (i < blocks)
		minos[i++] = save_this_block(&buf);

	i = 0;
	// printf("printing: \n");
	while (i < blocks)
	{
		minos[i][0]->x = 0;
		minos[i][0]->y = 0;
		// for (int z = 0; z < 4; z++)
		// 	printf("block%d: x:%d y:%d\n", z + 1, minos[i][z]->x , minos[i][z]->y);
		// printf("==============\n");
		i++;
	}
	return (minos);
}

static t_status	map_validator(char *buf)
{
	int		i;
	int		j;

	i = 0;
	while (buf[i] != '\0')
	{
		j = i-- + 4;
		while (++i < j)
			if (buf[i] != '.' && buf[i] != '#')
				return (Invalid);
		if (!CHECKNL(buf[i]) || !(i++))
			return (Invalid);
		if (i % 21 == 20 && !CHECKNL(buf[i]))
			return (Invalid);
		else if (i % 21 == 20 && i++)
			;
	}
	return (Valid);
}

static char		*reader(int fd)
{
	char 	*buf;
	short	b_read;

	buf = ft_strnew(666);
	if ((b_read = read(fd, buf, 666)) < 0)
		return (NULL);
	if (map_validator(buf) == Invalid)
	{	
		free(buf);
		return (NULL);
	}
	else
		return (buf);
}


char		**assemble(char width)
{
	char	**sol;
	int		i;
	int		j;

	i = 0;
	sol = malloc(sizeof(char *) * width);
	while (i < width)
	{
		j = 0;
		sol[i]  = malloc(sizeof(char) * width + 1);
		while (j < width + 1)
			sol[i][j++] = '.';
		sol[i][(int)width] = '\n';
		i++;
	}
	//solve(sol);
	return (sol);
}

void		map_op(char **map, char width, const char *token)
{
	int i;
	int	j;

	i = -1;
	if (ft_strcmp(token, "print") == 0)
	{
		while (++i < width)
			write(1, map[i], width + 1);
	}
	else if (ft_strcmp(token, "clean") == 0)
	{
		while (++i < width)
		{
			j = -1;
			while (++j < width)
				map[i][j] = '.';
		}
	}
}

int			fill(t_mino *m, t_poi *p, int mi, int width, int clean)
{
	char	replacer;
	short	i;

	i = 0;
	replacer = (clean) ? '.' : 'A' + mi;
	while (i < 4)
	{
		if (!((p->y + m->minos[mi][i]->y) < width) ||
			!((p->x + m->minos[mi][i]->x) < width) ||
			!(p->x >= 0) || !((m->map)[p->y + m->minos[mi][i]->y][p->x + m->minos[mi][i]->x] == 
			((clean) ? 'A' + mi : '.')))
			break ;
		i++;
	}
	free(p);
	if (i != 4)
		return (Invalid);
	i = -1;
	while (++i < 4)
		(m->map)[p->y + m->minos[mi][i]->y][p->x + m->minos[mi][i]->x] = replacer;
	return (Valid);
}


int			solve(t_mino *mino, int mino_i, int width, int bits)
{
	int			x;
	int			y;
	int			temp;

	if (bits == mino->filled)
		return (Valid);
	y = 0;
	while (y < width)
	{
		x = 0;
		while (x < width)
		{
			if (mino->map[y][x] == '.' && fill(mino, create_point(y, x), mino_i, width, 0))
			{
				bits |= 1UL << mino_i;
				if (solve(mino, next_block(bits, mino->length), width, bits))
					return (Valid);
				else {
					bits &= ~(1UL << mino_i);
					fill(mino, create_point(y, x), mino_i, width, 1);
				}
			}
			x++;
		}
		y++;
	}
	return (Invalid);
}

void		free_the_world(t_mino **mino)
{
	int		i;
	int		j;

	i = -1;
	while (++i < (*mino)->width)
		free((*mino)->map[i]);
	free((*mino)->map);
	i = -1;
	while (++i < (*mino)->length)
	{
		j = -1;
		while (++j < 4)
			free((*mino)->minos[i][j]);
		free((*mino)->minos[i]);
	}
	free((*mino));
}

int			main(int ac, char **av)
{
	t_mino	*mino;

	if (ac != 2 || !av[0])
		ft_errorexit("usage: fillit <filename>");
	char	*buf = reader(open(av[1], O_RDONLY));
	int	map_len = (int)ft_strlen(buf) + 1;
	mino = malloc(sizeof(t_mino));
	mino->length = map_len / 21;
	mino->minos = save_tetriminos(buf, mino->length);
	mino->width = ft_sqrt((mino->length) * 4);
	mino->map = assemble(mino->width);
	mino->filled = fill_bit(mino->length);
	while (42)
	{
		if (solve(mino, 0, mino->width , 0))
		{
			map_op(mino->map, mino->width, "print");
			break;
		}
		else
			mino->map = assemble(++mino->width);
	}
	free_the_world(&mino);
	return (0);
}
