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

static char		**map_op(char **map, char width, const char *token)
{
	int		i;
	int		j;
	char	**sol;

	i = -1;
	if (ft_strcmp(token, "print") == 0)
		while (++i < width)
			write(1, map[i], width + 1);
	else if (ft_strcmp(token, "create") == 0)
	{
		i = 0;
		sol = malloc(sizeof(char *) * width);
		while (i < width)
		{
			j = 0;
			sol[i] = malloc(sizeof(char) * width + 1);
			while (j < width + 1)
				sol[i][j++] = '.';
			sol[i][(int)width] = '\n';
			i++;
		}
		return (sol);
	}
	return (NULL);
}

static int		fill(t_mino *m, int y, int x, int mi, int clean)
{
	char	c;
	short	i;

	i = 0;
	c = (clean) ? '.' : 'A' + mi;
	while (i < 4)
	{
		if (!((y + m->minos[mi][i]->y) < m->width) ||\
			!((x + m->minos[mi][i]->x) < m->width) ||\
			!(x + m->minos[mi][i]->x >= 0) || \
			!((m->map)[y + m->minos[mi][i]->y][x + m->minos[mi][i]->x]\
			== ((clean) ? 'A' + mi : '.')))
			break ;
		i++;
	}
	if (i != 4)
		return (Invalid);
	i = -1;
	while (++i < 4)
		(m->map)[y + m->minos[mi][i]->y][x + m->minos[mi][i]->x] = c;
	return (Valid);
}

static int		solve(t_mino *mino, int mino_i, int width)
{
	int			x;
	int			y;

	if (mino_i == mino->length)
		return (Valid);
	y = -1;
	while (++y < width)
	{
		x = -1;
		while (++x < width)
			if (mino->map[y][x] == '.' && fill(mino, y, x, mino_i, 0))
			{
				if (solve(mino, mino_i + 1, width))
					return (Valid);
				else 
					fill(mino, y, x, mino_i, 1);
			}
	}
	return (Invalid);
}

static void		free_the_world(t_mino **mino, int map_only)
{
	int		i;
	int		j;

	i = -1;
	while (++i < (*mino)->width)
		free((*mino)->map[i]);
	free((*mino)->map);
	if (map_only)
		return ;
	i = -1;
	while (++i < (*mino)->length)
	{
		j = -1;
		while (++j < 4)
			free((*mino)->minos[i][j]);
		free((*mino)->minos[i]);
	}
	free((*mino)->minos);
	free((*mino));
}

int			main(int ac, char **av)
{
	t_mino	*mino;
	char	*buf;

	if (ac != 2 || !av[0])
		ft_errorexit("usage: fillit <filename>");
	if ((buf = reader(open(av[1], O_RDONLY))) == NULL)
		ft_errorexit("error");
	mino = malloc(sizeof(t_mino));
	mino->length = ((int)ft_strlen(buf) + 1) / 21;
	mino->minos = save_tetriminos(buf, mino->length);
	mino->width = ft_sqrt((mino->length) * 4);
	mino->map = map_op(NULL, mino->width, "create");
	if (validate_tetriminos(mino))
		while (!solve(mino, 0, mino->width))
		{
				free_the_world(&mino, 1);
				mino->map = map_op(NULL, ++mino->width, "create");
		}
	else 
	{
		free_the_world(&mino, 0);
		ft_errorexit("error");
	}
	map_op(mino->map, mino->width, "print");
	free_the_world(&mino, 0);
	return (0);
}