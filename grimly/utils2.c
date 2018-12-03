/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 09:04:56 by qpeng             #+#    #+#             */
/*   Updated: 2018/12/02 09:08:59 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "queue.h"

void	prompter(int ans)
{
	ft_putstr_fd("RESULT IN ", 1);
	ft_putnbr(--ans);
	ft_putstr_fd(" STEPS!\n", 1);
	free(g_visit);
	free(g_prev);
	free(g_r.list_array);
	free(g_c.list_array);
}

void	print_and_free(t_res *res, int ans)
{
	ft_putnbr(g_map_i.len);
	ft_putchar('x');
	ft_putnbr(g_map_i.wd);
	ft_putchar(g_map_i.ob);
	ft_putchar(g_map_i.ety);
	ft_putchar(g_map_i.pth);
	ft_putchar(g_map_i.en);
	ft_putchar(g_map_i.dst);
	ft_putchar('\n');
	print_map(res->map);
	free(res->map);
	free(res);
	prompter(ans);
}

BOOL	is_dupliacte(void)
{
	return ((g_map_i.ety == g_map_i.pth) || (g_map_i.ob == g_map_i.ety)\
	|| (g_map_i.dst == g_map_i.en) || (g_map_i.ob == g_map_i.en)\
	|| (g_map_i.dst == g_map_i.ob) || (g_map_i.dst == g_map_i.ety)\
	|| (g_map_i.dst == g_map_i.pth || (g_map_i.en == g_map_i.pth)\
	|| (g_map_i.en == g_map_i.ety) || (g_map_i.pth == g_map_i.ob)));
}

void	init(void)
{
	g_map_i.enp.x = -1;
	g_map_i.wd = 0;
	g_map_i.len = 0;
	g_map_i.ob = 0;
	g_map_i.ety = 0;
	g_map_i.pth = 0;
	g_map_i.en = 0;
	g_map_i.dst = 0;
	g_map_i.enp.y = -1;
	g_map_i.ext.x = -1;
	g_map_i.ext.y = -1;
}

int		init_queue(void)
{
	if (g_map_i.enp.x == -1 || g_map_i.enp.y == -1)
		return (ERROR);
	QUEUE(init)(g_map_i.len * g_map_i.wd + g_map_i.len, &g_r);
	QUEUE(init)(g_map_i.len * g_map_i.wd + g_map_i.len, &g_c);
	QUEUE(enqueue)(g_map_i.enp.y, &g_r);
	QUEUE(enqueue)(g_map_i.enp.x, &g_c);
	g_visit[g_map_i.enp.y][g_map_i.enp.x] = VISITED;
	return (VALID);
}
