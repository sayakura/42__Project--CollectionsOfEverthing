/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 07:58:51 by qpeng             #+#    #+#             */
/*   Updated: 2018/12/02 08:16:17 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_char_at(char *str, int ch)
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
