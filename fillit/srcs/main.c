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

static t_poi	**save_this_block(char **map)
{
	int 	i;
	int		b_i;
	t_poi	*poi;
	t_poi	**block;

	for (int i = 0; i < 21; i++)
		printf("%c", (*map)[i]);

	b_i = 0;
	i = 0;
	poi = malloc(sizeof(t_poi));
	block = malloc(sizeof(t_poi *) * 4);
	while ((*map)[i] != '#')
		i++;
	poi->x = (i % 5);
	poi->y = (i / 5);
	printf("i: [%d], x:%d, y:%d\n", i, poi->x, poi->y);
	block[b_i++] = poi;
	while (++i < 20 && b_i < 4)
	{
		poi = malloc(sizeof(t_poi));
		while ((*map)[i] != '#' && i < 20)
			i++;
		poi->x = (i % 5) - block[0]->x;
		poi->y = (i / 5) - (block[0]->y);
		printf("i: [%d], x:%d, y:%d\n", i, (i % 5) , (i / 5));
		block[b_i++] = poi;
	}
	*map += 21;
	printf("==========\n");
	return (block);
}

static t_poi	***save_tetriminos(char *buf, short blocks)
{
	short 	i;
	t_poi 	***minos;

	i = 0;
	minos = (t_poi ***)malloc(sizeof(t_poi**) * blocks);

	printf("saving all the blocks(total of %d blocks): \n", blocks);
	while (i < blocks)
		minos[i++] = save_this_block(&buf);

	i = 0;
	printf("printing: \n");
	while (i < blocks)
	{
		minos[i][0]->x = 0;
		minos[i][0]->y = 0;
		for (int z = 0; z < 4; z++)
			printf("block%d: x:%d y:%d\n", z + 1, minos[i][z]->x , minos[i][z]->y);
		printf("==============\n");
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

int			fill(char **map, t_mino m, t_poi p, int mi, int bi, char width)
{
	static char		replacer = 'A';

	map[p.y + m.minos[mi][bi]->y][p.x + m.minos[mi][bi]->x] = replacer;
	if (bi == 3)
	{
		replacer++;
		return (Valid);
	}
	if (p.y + m.minos[mi][bi + 1]->y <= width && p.x + m.minos[mi][bi + 1]->x <= width &&
		p.x + m.minos[mi][bi + 1]->x >= 0 &&
		map[p.y + m.minos[mi][bi + 1]->y][p.x + m.minos[mi][bi + 1]->x] == '.' &&
		fill(map, m, p, mi, bi + 1, width))
		return (Valid);
	else
	{
		map[p.y + m.minos[mi][bi]->y][p.x + m.minos[mi][bi]->x] = '.';
		return (Invalid);
	}
}

void		print_map(char **map, char width)
{
	int i;

	i = -1;
	while (++i < width)
		write(1, map[i], width + 1);
}

void			solve(char **map, t_mino mino, char mino_i, char width, char blocks)
{
	/*
	short		x;
	short		y;
	unsigned char	minos_i;
	unsigned char	block_i;
	*/
	t_poi poi;
	(void)blocks;
	while (mino_i <= mino.length)
	{
		poi.x = 0;
		poi.y = 0;
		while (poi.y < width && mino_i <= mino.length)
		{
			printf("%d %d\n", poi.x, poi.y);
			while (poi.x < width && mino_i <= mino.length)
			{
				while (map[(int)poi.y][(int)poi.x] == '.' )
					if (fill(map, mino, poi, mino_i, 0, width))
					{
						mino_i++;
						break ;
					}
				poi.x++;
			}
			if (poi.x >= width)
			{
				poi.x = 0;
				poi.y++;
			}
			else 
				break ;
		}
		if (mino_i == 4)
		{
			print_map(map, width);
			return ;
		}
	}
	print_map(map, width);
}


int			main(int ac, char **av)
{
	t_mino	mino;

	char	**map;

	if (ac != 2 || !av[0])
		ft_errorexit("usage: fillit <filename>");
	printf("%s\n", av[1]);
	char	*buf = reader(open(av[1], O_RDONLY));
	printf("Sample map: \n%s", buf);
	short	map_len = (short)ft_strlen(buf) + 1;
	mino.minos = save_tetriminos(buf, map_len / 21);
	mino.length = map_len / 21;
	map = assemble(ft_sqrt((map_len / 21) * 4)); 
	solve(map, mino, 0, ft_sqrt((map_len / 21) * 4), (map_len / 21));
	return (1);
}
