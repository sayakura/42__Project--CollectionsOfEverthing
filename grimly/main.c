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

int		g_dy[4] = {-1, 0, 0, 1};
int		g_dx[4] = {0, -1, 1, 0};
int		g_len = INT_MAX;

t_status	save_syms(char *str)
{
	int	len;
	int i;

	i = 0;
	len = ft_strlen(str);
	g_map_i.dst = str[--len];
	g_map_i.en = str[--len];
	g_map_i.pth = str[--len];
	g_map_i.ety = str[--len];
	g_map_i.ob = str[--len];
	g_map_i.len = ft_atoi(str);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i++] != 'x')
		return (ERROR);
	g_map_i.wd = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	if (i != len)
		return (ERROR);
	return (VALID);
}

t_status	read_fst_line(int fd)
{
	char 		buffer[8];
	char		*str;
	t_status	status;

	str = ft_strnew(15);
	if (read(fd, buffer, 8) != 8)
		return (ERROR);
	if (ft_c_at(buffer, '\n') != -1 || ft_c_at(buffer, '\0') != -1)
		return (ERROR);
	ft_strncat(str, buffer, 8);
	while (read(fd, buffer, 1) != 0)
	{
		if (buffer[0] == '\n')
			break ;
		ft_strncat(str, buffer, 1);
	}
	status = save_syms(str);
	free(str);
	return status;
}


t_status	read_stdin_fl(char *in)
{
	char 		buffer[8];
	char		*str;
	t_status	status;
	int 		i;

	i = 0;
	str = ft_strnew(15);
	while (i < 8)
	{
		buffer[i] = *in++;
		if (buffer[i++] == '\0')
			return (ERROR);
	}
	if (ft_c_at(buffer, '\n') != -1 || ft_c_at(buffer, '\0') != -1)
		return (ERROR);
	ft_strncat(str, buffer, 8);
	while (*in != '\0')
	{
		if (*in == '\n')
			break ;
		ft_strncat(str, in, 1);
	}
	status = save_syms(str);
	free(str);
	return status;
}


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
		//printf("%d %d\n", yy, xx);
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
	queue(init)(g_map_i.len * g_map_i.wd,  &r);
	queue(init)(g_map_i.len * g_map_i.wd,  &c);
	queue(enqueue)(en.y, &r);
	queue(enqueue)(en.x, &c);
	g_visit[en.x][en.y] = VISITED;
	while (!r.isEmpty)
	{
		x = queue(dequeue)(&c);
		y = queue(dequeue)(&r);
		if (map[y][x] == g_map_i.dst)
		{
			g_map_i.ext.x = x;
			g_map_i.ext.y = y;
			printf("ext: %d %d\n", g_map_i.ext.y, g_map_i.ext.x);
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
	//t_list	**exts;

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

char	**read_map(int fd)
{
	int		i;
	char	**map;

	i = 0;
	ft_create_dp(g_map_i.len, g_map_i.wd);
	map = (char **)malloc(sizeof(char *) * g_map_i.len);
	while (i < g_map_i.len)
	{
		map[i] = (char *)malloc(sizeof(char) * g_map_i.wd + 1);
		read(fd, map[i], g_map_i.wd + 1);
		i++;      
	}
	return (map);
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

void	free_map(t_res *res)
{
	int	i;

	i = 0;
	while (i < g_map_i.len)
	{
		free(res->map[i]);
		free(g_visit[i]);
		free(g_prev[i]);
		i++;
	}
}

t_res	*parser(int fd)
{
	t_res   *res;

	res = (t_res *)malloc(sizeof(t_res));
	res->status = read_fst_line(fd);
	res->map = read_map(fd);
	close(fd);
	return (res);
}

t_res	*stdin_parser(int fd)
{
	t_res   *res;

	res = (t_res *)malloc(sizeof(t_res));
	res->status = read_fst_line(fd);
	res->map = read_map(fd);
	close(fd);
	return (res);
}

int		main(int ac, char **av)
{
	int     fd;
	t_res   *res;
	int		ans;

	ans = 0;
	if (ac < 2)
	{
		ft_putstr_fd("MAP ERROR\n", 2);
		return (0);
	}
	av++;
	while (*av)
	{
		fd = open(*av++, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("MAP ERROR\n", 2);
			return (0);
		}
		else
		{
			res = parser(fd);
			print_map(res->map);
			printf("en:[%c] ob:[%c] dst:[%c] ety:[%c] wd:[%d] len:[%d]\n", g_map_i.en, g_map_i.ob, g_map_i.dst, g_map_i.ety, g_map_i.wd,  g_map_i.len);
			ans = map_solve(res->map);
			if (ans == ERROR)
			{
				ft_putstr_fd("MAP ERROR\n", 2);
				close(fd);
				continue ;
			}
			print_map(res->map);
			ft_putstr_fd("RESULT IN ", 1);
			ft_putnbr(ans);
			ft_putstr_fd(" STEPS!\n", 1);
			//free_map(res);
		}
		close(fd);
	}
	return (0);
}
