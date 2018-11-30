/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 18:41:50 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/24 18:42:27 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_ls.h"
const char *g_ubase = "0123456789ABCDEF";
const char *g_lbase = "0123456789abcdef";

char	*ft_strdup(const char *str)
{
	int		len;
	char	*ptr;
	int		index;

	index = 0;
	len = ft_strlen(str) + 1;
	if (!(ptr = (char *)p(sizeof(char) * len)))
		return (NULL);
	while (str[index] != '\0')
	{
		ptr[index] = str[index];
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}

int		ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}


char	*ft_adjustspaces(char *str, size_t max)
{
	size_t	s_strlen;
	size_t	index;
	char	*ptr;
	size_t	pilot;


	s_strlen = ft_strlen(str);
	pilot = max - s_strlen;
	if (pilot == 0)
		return (str);
	index = s_strlen;
	ptr = (char *)p(sizeof(char) * max + 1);
	ptr[max] = '\0';
	while (--max != 0)
	{
		if (max < pilot)
			ptr[max] = ' ';
		else
			ptr[max] = str[--s_strlen];
	}
	ptr[max] = ' ';
	return (ptr);
}


size_t	ft_numlen(size_t num)
{
	size_t		size;

	size = 1;
	while (num /= 10)
		size++;
	return (size);
}


void	initial_arr(size_t *arr, size_t size)
{
	size_t		index;

	index = 0;
	while (index < size)
	{
		arr[index] = 0;
		index++;
	}
}

char	*ft_lltoa(long long num, int base, signed char isupper)
{
	char		*res;
	size_t		size;
	char		neg;
	long long	temp;

	neg = (base == 10 && num < 0) ? 1 : 0;
	size = (num < 0) ? 3 : 2;
	temp = num;
	while ((temp /= base) != 0)
		size++;
	if (!(res = (char *)p(sizeof(char) * size)))
		return (NULL);
	res[--size] = '\0';
	res[--size] = (isupper == 1) ? g_ubase[ABS(num % base)] :\
									g_lbase[ABS(num % base)];
	while (num /= base)
		res[--size] = (isupper == 1) ? g_ubase[ABS(num % base)] :\
									g_lbase[ABS(num % base)];
	if (base == 10 && neg == 1)
		res[--size] = '-';
	return (res);
}