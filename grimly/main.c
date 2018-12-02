/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 22:14:17 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/22 22:14:17 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "queue.h"
#include <stdio.h>
#include "libft/libft.h"

#define __PROMPT__(ans) 	ft_putstr_fd("RESULT IN ", 1); \
							ft_putnbr(--ans);\
							ft_putstr_fd(" STEPS!\n", 1);

#define __PRINTHEADER__()	ft_putnbr(g_map_i.len);\
							ft_putchar('x');\
							ft_putnbr(g_map_i.wd);\
							ft_putchar(g_map_i.ob);\
							ft_putchar(g_map_i.ety);\
							ft_putchar(g_map_i.pth);\
							ft_putchar(g_map_i.en);\
							ft_putchar(g_map_i.dst);\
							ft_putchar('\n');

const int	g_dy[4] = {-1, 0, 0, 1};
const int	g_dx[4] = {0, -1, 1, 0};

void	explore_cells(int y, int x, t_queue	*r, t_queue	*c, int *node_next, char **map)
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
		queue(enqueue)(yy, r);
		queue(enqueue)(xx, c);
	}
}

int		map_solve_helper(t_poi en, char **map)
{
	t_queue	r;
	t_queue	c;
	bool reached_end;
	int x;
	int y;
	int nodes_here;
	int nodes_next;
	int cnt;
	
	nodes_here = 1;
	nodes_next = 0;
	reached_end = false;
	cnt = 0;
	queue(init)(g_map_i.len * g_map_i.wd + g_map_i.len,  &r);
	queue(init)(g_map_i.len * g_map_i.wd + g_map_i.len,  &c);
	queue(enqueue)(en.y, &r);
	queue(enqueue)(en.x, &c);
	g_visit[en.y][en.x] = VISITED;
	while (!r.isEmpty)
	{
		x = queue(dequeue)(&c);
		y = queue(dequeue)(&r);
		if (map[y][x] == g_map_i.dst)
		{
			g_map_i.ext.y = y;
			g_map_i.ext.x = x;
			reached_end = true;
			break ;
		}
		explore_cells(y, x, &r, &c, &nodes_next, map);
		nodes_here--;
		if (nodes_here == 0)
		{
			nodes_here = nodes_next;
			nodes_next = 0;
			cnt++;
		}
	}
	if (reached_end)
		return (cnt);
	else
		return (-1);
}

t_status	map_solve(char **map)
{
	int 	r;
	int 	c;
	t_poi	en;
	t_poi	*ext;

	en.x = -1;
	r = 0;
	while (r < g_map_i.len)
	{
		c = 0;
		while (c < g_map_i.wd)
		{
			if (map[r][c] == g_map_i.en)
			{
				if (en.x != -1)
					return (ERROR);
				en.x = c;
				en.y = r;
				g_map_i.enp.x = c;
				g_map_i.enp.y = r;
			}
			if (map[r][c] != g_map_i.ety && map[r][c]  != g_map_i.ob\
				&& map[r][c] != g_map_i.dst &&map[r][c]  != g_map_i.en)
				return (ERROR);
			c++;
		}
		r++;
	}
	return (map_solve_helper(en, map));
}

void	print_map(char **map)
{
	int	i;
	int j;
	t_poi curr;
	 
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



int		main(int ac, char **av)
{
	int     fd;
	t_res   *res;
	int		ans;
	int i;

	i = 1;
	ans = 0;
	while (i < ac || (i == ac && ac == 1))
	{
		fd = (ac == 1) ? 0 : open(av[i], O_RDONLY);
		res = (fd == -1) ? NULL : parser(fd);
		if (res == NULL || res->status == ERROR || (ans = map_solve(res->map)) <= 0)
		{
			i++;
			ft_putstr_fd("MAP ERROR\n", 2);
			close(fd);
			continue ;
		}
		__PRINTHEADER__();
		print_map(res->map);
		__PROMPT__(ans);
		close(fd);
		i++;
	}
	return (0);
}