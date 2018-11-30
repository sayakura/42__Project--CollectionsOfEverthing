/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 18:10:06 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/10 18:10:06 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_ls.h"

uint8_t	g_flags;
t_args	g_OBJS;

int		ft_save_flags(char *str)
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
		else
		{
			printf("ls: illegal option -- %c\n", str[i]);
			printf("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
			return (false);
		}
		++i;
	}
	return (true);
}

int 	ft_div_args(t_args *args, char *path)
{
	struct 		stat f_info;
	if (stat(path, &f_info) < 0)
	{
		printf("ls: %s: No such file or directory\n", path);
		return (FAILED);
	}
	if (S_ISDIR(f_info.st_mode))
		u_lst_append(args->d_args, path);
	else
		u_lst_append(args->f_args, path);
	return (SUCCESS);
}


t_args *ft_get_args(char **av)
 {
	uint8_t			i;
	uint8_t			j;
	t_bool			is_flag;
	t_args			*args_lst;

	args_lst = ()
	i = 0;
	is_flag = 1;
	while (av[++i])
	{
		j = 0;
		if (av[i][0] == '-' && is_flag)
		{
			if (ft_save_flags(av[i]) == false)
				return (NULL);
			continue ;
		}
		else
		{
			is_flag = 0;
			u_lst_append(args_lst, av[i]);
		}
	}
	return (args_lst);
 }
