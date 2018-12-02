/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 22:22:26 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/22 22:22:26 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include "libft/libft.h"

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

void	ft_create_dp(int len, int wd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	g_visit = (bool **)malloc(sizeof(bool *) * len);
	g_prev = (t_poi **)malloc(sizeof(t_poi *) * len);
	while (i < len)  
	{
		g_visit[i] = (bool *)malloc(sizeof(bool) * wd);
		g_prev[i] = (t_poi *)malloc(sizeof(t_poi) * wd);
		j = 0;
		while (j < wd)
		{
			g_visit[i][j] = NOT_VISITED;
			g_prev[i][j].x = -1;
			g_prev[i][j].y = -1;
			j++;
		}
		i++;
	}
	return ;
}

t_status	read_fst_line(int fd)
{
	char 		buffer[8];
	char		*str;
	t_status	status;

	str = ft_strnew(15);
	if (read(fd, buffer, 8) != 8)
		return (ERROR);
	if (ft_char_at(buffer, '\n') != -1 || ft_char_at(buffer, '\0') != -1)
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

t_res	*parser(int fd)
{
	t_res   *res;

	res = (t_res *)malloc(sizeof(t_res));
	res->status = read_fst_line(fd);
	if (res->status == ERROR)
	{
		close(fd);
		return (res);
	}	
	res->map = read_map(fd);
	close(fd);
	return (res);
}