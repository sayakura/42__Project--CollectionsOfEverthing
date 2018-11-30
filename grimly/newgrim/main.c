/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 22:24:32 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/28 22:24:32 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"


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

t_status    parse_stdin(char *str)
{
    char        *dst;
	t_status	status;

    dst = ft_strnew(15);
    while (*str != '\n')
    {
		ft_strncat(dst, str, 1);
        str++;
    }
    status = save_syms(dst);
    free(dst);
	return (status);
}

t_status read_map(int fd)
{
	int		i;
	char	*map;
    size_t  size;
    t_status    s;
    char    buffer[1];

    size = g_map_i.len * g_map_i.wd + g_map_i.len;
	i = 0;
	ft_create_dp(g_map_i.len, g_map_i.wd);
	map = (char *)malloc(sizeof(char) * size);
    if ((read(fd, map, size)) != size)
        return (ERROR);
    if ((read(fd, buffer, size)) != 0)
        return (ERROR);
	return (VALID);
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


int		main(int ac, char **av)
{
	int     fd;
	t_res   *res;
	int		ans;
    char    *buffer;

	ans = 0;
	if (ac < 2)
	{
        buffer = (char *)malloc(sizeof(char) * 1500000);
        if ((read(1, buffer, 1500000) < 8))
        {
            ft_putstr_fd("MAP ERROR\n", 2);
            return (0);
        }
        parse_stdin(buffer);
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
			
		}
		close(fd);
	}
	return (0);
}
