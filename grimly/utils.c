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

void    ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void    ft_putstr_fd(const char *str, int fd)
{
	while (*str)
		ft_putchar_fd(*str++, fd);
}

size_t		ft_strlen(const char *str)
{
	int		len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int		ft_c_at(char *str, int ch)
{
	char			c;
	unsigned int	index;
	size_t			len;

	len = ft_strlen(str);
	index = 0;
	c = ch;
	while (index < len)
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	size_t		len;
	size_t		index;

	index = 0;
	len = ft_strlen(s1);
	while (index < n && s2[index])
	{
		s1[len] = s2[index];
		len++;
		index++;
	}
	s1[len] = '\0';
	return (s1);
}

char	*ft_strnew(size_t size)
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * size + 1);
	while (i < size + 1)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}