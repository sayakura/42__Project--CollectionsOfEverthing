/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 07:29:25 by qpeng             #+#    #+#             */
/*   Updated: 2018/12/06 07:30:12 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/fillit.h"

static t_poi	**save_this_block(char **map)
{
	int		i;
	int		b_i;
	t_poi	*poi;
	t_poi	**block;

	b_i = 0;
	i = 0;
	poi = malloc(sizeof(t_poi));
	block = malloc(sizeof(t_poi *) * 4);
	while ((*map)[i] != '#')
		i++;
	poi->x = (i % 5);
	poi->y = (i / 5);
	block[b_i++] = poi;
	while (++i < 20 && b_i < 4)
	{
		poi = malloc(sizeof(t_poi));
		while ((*map)[i] != '#' && i < 20)
			i++;
		poi->x = (i % 5) - block[0]->x;
		poi->y = (i / 5) - (block[0]->y);
		block[b_i++] = poi;
	}
	*map += 21;
	return (block);
}

t_poi			***save_tetriminos(char *buf, short blocks)
{
	short	i;
	t_poi	***minos;

	i = 0;
	minos = (t_poi ***)malloc(sizeof(t_poi**) * blocks);
	while (i < blocks)
		minos[i++] = save_this_block(&buf);
	i = 0;
	while (i < blocks)
	{
		minos[i][0]->x = 0;
		minos[i][0]->y = 0;
		i++;
	}
	return (minos);
}

int				validate_tetriminos(t_mino *mino)
{
	int	i;
	int	j;
	int	z;
	int	connections;

	i = -1;
	connections = 0;
	while (++i < mino->length)
	{
		j = -1;
		connections = 0;
		while (++j < 4)
		{
			z = j;
			while (++z < 4)
				if (((ABS((mino->minos[i][j]->x - mino->minos[i][z]->x)) == 1)
				&& mino->minos[i][j]->y == mino->minos[i][z]->y) ||
				((ABS((mino->minos[i][j]->y - mino->minos[i][z]->y)) == 1)
				&& mino->minos[i][j]->x == mino->minos[i][z]->x))
					connections += 2;
		}
		if (connections < 6)
			return (Invalid);
	}
	return (Valid);
}

static t_status	map_validator(char *buf)
{
	int		i;
	int		j;
	int		blkcnt;

	blkcnt = 0;
	i = 0;
	while (buf[i] != '\0')
	{
		j = i-- + 4;
		while (++i < j)
			if (buf[i] != '.' && buf[i] != '#')
				return (Invalid);
			else if (buf[i] == '#')
				blkcnt++;
		if (!CHECKNL(buf[i]) || !(i++))
			return (Invalid);
		if ((i % 21 == 20 && blkcnt != 4) ||\
			(i % 21 == 20 && !CHECKNL(buf[i])))
			return (Invalid);
		if (i % 21 == 20 && i++)
			blkcnt = 0;
	}
	return (Valid && (i % 21 == 0));
}

char			*reader(int fd)
{
	char	*buf;
	short	b_read;

	buf = ft_strnew(666);
	if (fd < 0 || (b_read = read(fd, buf, 666)) <= 0)
		return (NULL);
	if (b_read > 547)
		return (NULL);
	if (map_validator(buf) == Invalid)
	{
		free(buf);
		return (NULL);
	}
	else
		return (buf);
}
