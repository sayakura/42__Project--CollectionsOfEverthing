/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:45:36 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/10 17:45:36 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "b_ls.h"

extern uint8_t	g_flags;
extern t_args	g_OBJS;




void	ft_ls(char *av)
{


}

int 	main(int ac, char **av)
{
	if (ac == 1)
			ft_ls(".");
	else
		ft_get_args(av);
	return (0);
}