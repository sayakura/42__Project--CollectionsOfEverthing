/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_helper.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:09:12 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/24 01:09:13 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_ls.h"

uint8_t	g_flags;

void	ft_save_flags(char *str)
{
	uint8_t			i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'l')
			g_flags |= f_l;
		else if (str[i] == 'a')
			g_flags |= f_a;
		else if (str[i] == 'r')
			g_flags |= f_r;
		else if (str[i] == 't')
			g_flags |= f_t;
		++i;
	}
}

t_list	**ft_get_args(char **av)
 {
	uint8_t			i;
	uint8_t			j;
	t_bool			is_flag;
	t_list			**args_lst;

	i = 0;
	is_flag = 1;
	args_lst = malloc(sizeof(t_list *));
	*args_lst = NULL;
	while (av[++i])
	{
		j = 0;
		if (av[i][0] == '-' && is_flag)
		{
			ft_save_flags(av[i]);
			continue ;
		}
		else
		{
			is_flag = 0;
			ft_lstappend(args_lst, av[i]);
		}
	}
	return (args_lst);
 }


char		*ft_add_prefix(char *path, char *basename)
{
	uint8_t	total;
	char 	*ptr;
	uint8_t	index;
	uint8_t	i2;

	i2 = 0;
	if (path[0] == '.')
		return (basename);
	index = 0;
	total = ft_strlen(path) + ft_strlen(basename) + 1;
	ptr = p(sizeof(total));
	while (path[index])
	{
		ptr[index] = path[index];
		index++;
	}
	ptr[index++] = '/';
	while (index < total)
	{
		ptr[index] = basename[i2];
		index++;
		i2++;
	}
	ptr[index] = '\0';
	return (ptr);
}


uint8_t		ft_strlen(const char* str)
{
	uint8_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char    *ft_strcpy(char *dest, char *src)
{
	uint8_t  index;

	index = 0;
	while ((dest[index] = src[index]) != '\0')
		index++;
	dest[index] = '\0';
	return (dest);
}

char    *ft_get_basename(const char *str)
{
	uint8_t  len;
	int8_t  index; 
	char    *ptr;
    
	len = ft_strlen(str);
	index = len - 1;
	while (index != -1 && str[index] != '/')
		index--;
	if (index == -1)
		return (char *)(str);
	ptr = p(sizeof(char) * (len - index) + 1);
	ft_strcpy(ptr, (char *)(str + ++index));
	return (ptr);
}
