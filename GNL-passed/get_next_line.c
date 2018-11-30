/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 19:39:00 by qpeng             #+#    #+#             */
/*   Updated: 2018/11/24 16:44:04 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	helper(int fd, char **line, char **bfs)
{
	int		len;
	char	*temp;

	len = 0;
	while (bfs[fd][len] != '\n' && bfs[fd][len] != '\0')
		len++;
	if (bfs[fd][len] == '\n')
	{
		*line = ft_strsub(bfs[fd], 0, len);
		temp = ft_strdup(bfs[fd] + len + 1);
		free(bfs[fd]);
		bfs[fd] = temp;
		if (bfs[fd][0] == '\0')
			ft_strdel(&bfs[fd]);
	}
	else
	{
		*line = ft_strdup(bfs[fd]);
		ft_strdel(&bfs[fd]);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char	*bfs[65535];
	int			b_read;
	char		buff[BUFF_SIZE + 1];
	char		*temp;

	if (fd < 0 || line == NULL)
		return (-1);
	while ((b_read = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[b_read] = '\0';
		if (bfs[fd] == NULL)
			bfs[fd] = ft_strnew(1);
		temp = ft_strjoin(bfs[fd], buff);
		free(bfs[fd]);
		bfs[fd] = temp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (b_read < 0)
		return (-1);
	if (b_read == 0 && bfs[fd] == NULL)
		return (0);
	return (helper(fd, line, bfs));
}
