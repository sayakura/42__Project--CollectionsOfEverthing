/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 02:56:49 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/20 19:43:47 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_headers.h"

const char *g_ubase = "0123456789ABCDEF";
const char *g_lbase = "0123456789abcdef";

int		ft_isalpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

size_t	ft_strlen(const char* str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *str)
{
	int		len;
	char	*ptr;
	int		index;

	index = 0;
	len = ft_strlen(str) + 1;
	ptr = (char *)malloc(sizeof(char) * len);
	if (!ptr)
		return (NULL);
	while (str[index] != '\0')
	{
		ptr[index] = str[index];
		index++;
	}
	ptr[index] = '\0';
	return (ptr);
}

void	ft_lstappend(t_list **list, void *data)
{
	t_list	*node;
	t_list	*last;

	node = malloc(sizeof(node));
	last = malloc(sizeof(last));
	node->data = data;
	node->next = NULL;
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	last = *list;
	while (last->next != NULL)
		last = last->next;
	last->next = node;
}

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t		index;
	const char	*s;
	char		*d;

	d = dst;
	s = src;
	index = 0;
	while (index < n)
	{
		d[index] = s[index];
		index++;
	}
	return (d);
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

size_t	ft_numlen(size_t num)
{
	size_t		size;

	size = 1;
	while (num /= 10)
		size++;
	return (size);
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
	if (!(res = (char *)malloc(sizeof(char) * size)))
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
	ptr = (char *)malloc(sizeof(char) * max + 1);
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

char	*ft_add_space_end(char *str, size_t max)
{
	size_t	s_strlen;
	size_t	index;
	char	*ptr;
	size_t	pilot;

	s_strlen = ft_strlen(str);
	pilot = s_strlen;
	if (pilot == 0)
		return (str);
	index = 0;
	ptr = (char *)malloc(sizeof(char) * max + 1);
	ptr[max] = '\0';
	while (index < max)
	{
		if (index >= pilot)
			ptr[index] = ' ';
		else
			ptr[index] = str[index];
		index++;
	}
	return (ptr);
}

int 	ft_comptr(char *s1, char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] == s2[index])
	{
		if (s1[index] == '\0')
			return (0);
		index++;
	}
	return (unsigned char)s1[index] - (unsigned)s2[index];
}

int 		ft_if_contain(char *arr, char flag, size_t n)
{
	size_t		index;

	if (!arr)
		return (0);
	index = 0;
	while (arr[index] && n--)
	{
		if (flag == arr[index])
			return (1);
		index++;
	}
	return (0);
}

int 		ft_if_in_lst(t_list **target_list, void *data)
{
	t_list 	*head;

	head = *target_list;
	while (head)
	{
		if (ft_comptr((char *)head->data, (char *)data) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}

char		*ft_strpre(char *str1, char *str2)
{
	size_t	total;
	char 	*ptr;
	size_t	index;
	size_t	i2;

	i2 = 0;
	if (str1[0] == '.')
		return (str2);
	index = 0;
	total = ft_strlen(str1) + ft_strlen(str2) + 1;
	ptr = malloc(sizeof(total));
	while (str1[index])
	{
		ptr[index] = str1[index];
		index++;
	}
	ptr[index++] = '/';
	while (index < total)
	{
		ptr[index] = str2[i2];
		index++;
		i2++;
	}
	
	ptr[index] = '\0';
	return (ptr);
}

char    *ft_get_filename(char *path)
{
    size_t index;
    size_t len;
    size_t len2;
    size_t index3;
    char *ptr;
    
    index3 = 0;
    len = ft_strlen(path);
    index = 0;
    while (path[index] && path[index] != '/')
        index++;
    if (index == len)
        return (path);
    len2 = len - ++index;
    ptr = malloc(sizeof(len2 + 1));
    while (index3 < len2)
    {
        ptr[index3] = path[index];
        index3++;
        index++;
    }
    ptr[index3] = '\0';
    return (ptr);
}