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
#include <stdio.h>

/*
** Read the map in to a bufer called buf.
** Ultimate tricky code.
*/

#define CHECKNL(c) (c == '\0' || c == '\n')
#define COX(num, index, rx)  ((num - (num + index - (num % 5))) - rx)
#define COY(num, index, ry)  ((((num / 5) + index) %  5) - ry)

static t_list	**save_tetriminos(char *buf)
{
	short 	i;
	char	index;

	t_list	*minos[26];
	/*
	t_list	**minos;
	t_list 	*temp;

	minos = malloc(sizeof(t_list **));
	*minos = temp;*/
	i = 0;
	index = 0;
	while (buf[i] != '\0')
	{
		//.temp = ft_lstnew(NULL, 0);
		while (buf[i] != '#')
			i++;
		/*
		((t_poi *)(temp->content = malloc(sizeof(t_poi))))->x = COX(i, index, 0);
		((t_poi *)(temp->content))->y = -COX(i, index, 0);
		 printf("x: %d  y: %d, i: %d\t", ((t_poi *)(temp->content))->x,  ((t_poi *)(temp->content))->y, i);
*/		while (i % 21 != 20)
		{
			while (buf[i] != '#')
				i++;
			printf("x:%d y:%d i:%d\n", COX(i, index, 0), -COY(i, index, 0), i);
			
			i++;
			 if (i >= 21)
				break ;
		}
		break ;
	}
	return (minos);
}

static t_status	map_validator(char *buf)
{
	int		i;
	int		j;

	i = 0;
	while (buf[i] != '\0')
	{
		j = i-- + 4;
		while (++i < j)
			if (buf[i] != '.' && buf[i] != '#')
				return (Invalid);
		if (!CHECKNL(buf[i]) || !(i++))
			return (Invalid);
		if (i % 21 == 20 && !CHECKNL(buf[i]))
			return (Invalid);
		else if (i % 21 == 20 && i++)
			;
	}
	return (Valid);
}

static char		*reader(int fd)
{
	char 	*buf;
	short	b_read;

	buf = ft_strnew(666);
	if ((b_read = read(fd, buf, 666)) < 0)
		return (NULL);
	if (map_validator(buf) == Invalid)
	{	
		free(buf);
		return (NULL);
	}
	else
		return (buf);
}

int			main(int ac, char **av)
{
	if (ac != 2 || !av[0])
		ft_errorexit("usage: fillit <filename>");
	char *buf = reader(open(av[1], O_RDONLY));
	printf("%s\n", buf);
	save_tetriminos(buf);
	if (buf)
		free(buf);
	return (1);
}
