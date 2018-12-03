/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 22:14:17 by qpeng             #+#    #+#             */
/*   Updated: 2018/12/02 22:02:03 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "queue.h"

const int	g_dy[4] = {-1, 0, 0, 1};
const int	g_dx[4] = {0, -1, 1, 0};
int			g_x;
int			g_y;
int			g_nodes_here;
int			g_nodes_next;
int			g_cnt;

void		explore_cells(int y, int x, int *node_next, char **map)
{
	int i;
	int xx;
	int yy;

	i = 0;
	while (i < 4)
	{
		xx = x + g_dx[i];
		yy = y + g_dy[i];
		i++;
		if (xx < 0 || yy < 0)
			continue ;
		if (xx >= g_map_i.wd || yy >= g_map_i.len)
			continue ;
		if (g_visit[yy][xx])
			continue ;
		if (map[yy][xx] == g_map_i.ob)
			continue ;
		(*node_next)++;
		g_visit[yy][xx] = VISITED;
		g_prev[yy][xx].x = x;
		g_prev[yy][xx].y = y;
		QUEUE(enqueue)(yy, &g_r);
		QUEUE(enqueue)(xx, &g_c);
	}
}

int			map_solve_helper(char **map)
{
	g_nodes_here = 1;
	g_nodes_next = 0;
	g_cnt = 0;
	if (init_queue() == ERROR)
		return (-1);
	while (!g_r.is_empty)
	{
		g_x = QUEUE(dequeue)(&g_c);
		g_y = QUEUE(dequeue)(&g_r);
		if (map[g_y][g_x] == g_map_i.dst)
		{
			g_map_i.ext.y = g_y;
			g_map_i.ext.x = g_x;
			return (g_cnt);
		}
		explore_cells(g_y, g_x, &g_nodes_next, map);
		g_nodes_here--;
		if (g_nodes_here == 0)
		{
			g_nodes_here = g_nodes_next;
			g_nodes_next = 0;
			g_cnt++;
		}
	}
	return (-1);
}

t_status	map_solve(char **map)
{
	int		r;
	int		c;
	t_poi	*ext;

	r = 0;
	while (r < g_map_i.len)
	{
		c = 0;
		while (c < g_map_i.wd)
		{
			if (map[r][c] == g_map_i.en)
			{
				if (g_map_i.enp.x != -1)
					return (ERROR);
				g_map_i.enp.x = c;
				g_map_i.enp.y = r;
			}
			if (map[r][c] != g_map_i.ety && map[r][c] != g_map_i.ob\
				&& map[r][c] != g_map_i.dst && map[r][c] != g_map_i.en)
				return (ERROR);
			c++;
		}
		r++;
	}
	return (map_solve_helper(map));
}

void		print_map(char **map)
{
	int		i;
	int		j;
	t_poi	curr;

	i = 0;
	curr.x = g_map_i.ext.x;
	curr.y = g_map_i.ext.y;
	curr = g_prev[curr.y][curr.x];
	while (g_prev[curr.y][curr.x].x != -1)
	{
		if (curr.y == g_map_i.enp.y && curr.x == g_map_i.enp.x)
			break ;
		map[curr.y][curr.x] = g_map_i.pth;
		curr = g_prev[curr.y][curr.x];
	}
	while (i < g_map_i.len)
	{
		write(1, map[i], g_map_i.wd + 1);
		i++;
	}
}

int			main(int ac, char **av)
{
	int		fd;
	t_res	*res;
	int		ans;
	int		i;

	i = 1;
	ans = 0;
	while (i < ac || (i == ac && ac == 1))
	{
		init();
		fd = (ac == 1) ? 0 : open(av[i], O_RDONLY);
		res = (fd == -1) ? NULL : parser(fd);
		if (res == NULL || res->status == ERROR ||\
		(ans = map_solve(res->map)) <= 0)
		{
			i++;
			ft_putstr_fd("MAP ERROR\n", 2);
			close(fd);
			continue ;
		}
		print_and_free(res, ans);
		close(fd);
		i++;
	}
	return (0);
}
