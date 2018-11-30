/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 00:00:25 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/23 00:00:25 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int 	ft_isspace(char c)
{
	return (c == ' ' ||
			c == '\t' ||
			c == '\n' ||
			c == '\f' ||
			c == '\v' ||
			c == '\r' ||
			c == '\t');
}

int		ft_atoi(const char *str)
{
	unsigned long long	result;
	unsigned int		index;
	char				sign;

	index = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '+' || str[index] == '-')
	{
		if (str[index] == '-')
			sign = 0;
		index++;
	}
	while (ft_isdigit(str[index]))
	{
		result = result * 10 + (str[index] - '0');
		if (result > 9223372036854775807)
			return (sign ? (-1) : (0));
		index++;
	}
	return (int)((sign) ? (result) : (-result));
}
t_list 	*ft_new_node(void *data)
{
	t_list *node;
	
	if((node = (t_list *)malloc(sizeof(t_list))) == NULL)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}
void	ft_lst_append(t_list **ref, void *data)
{
	t_list	*head;

	head = *ref;
	if (*ref == NULL)
		*ref = ft_new_node(data);
	else
	{
		while (head && head->next)
			head = head->next;
		head->next = ft_new_node(data);
	}
}

/*
t_path	*ft_new_path()
{
	t_path *path;

	if ((path = (t_path *)malloc(sizeof(t_path))) == NULL)
		return (NULL);
	path->head = NULL;
	path->tail = NULL;
	return (path);
}

t_path *ft_path_cpy(t_path *new)
{
	t_path *cpy;

	cpy = ft_new_path();
	cpy->head = new->head;
	cpy->tail = new->head;
	new->head = new->head->next;
	while (new->head)
	{
		cpy->tail->next = new->head;
		cpy->tail = cpy->tail->next;
		new->head = new->head->next;
	}
	return (cpy);
}

void	ft_add_path(t_list **path, t_path *new)
{
	t_list *head;
	t_list *node;

	node = ft_new_lst(ft_path_cpy(new));
	if (*path == NULL)
	{
		*path = node;
		return ;
	}
	head = *path;
	while (head && head->next)
		head = head->next;
	head->next = node;
}

void	ft_pop_back(t_path *path)
{
	path->tail = path->tail->prev;
	path->tail = NULL;
}

void	ft_apnd_cur(t_path *path, t_poi poi)
{
	t_poi *cur;
	
	cur = (t_poi *)malloc(sizeof(t_poi));
	cur->x = poi.x;
	cur->y = poi.y;
	cur->prev = NULL;
	cur->next = NULL;
	if (path->head == NULL)
	{
		path->head = cur;
		path->tail = cur;
		return ;
	}
	cur->prev = path->tail->next;
	path->tail->next = cur;
	path->tail = cur;
}
*/

void	ft_create_dp(int len, int wd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	g_visit = (bool **)malloc(sizeof(bool *) * wd);
	g_prev = (t_poi **)malloc(sizeof(t_poi *) * wd);
	while (i < wd)
	{
		g_visit[i] = (bool *)malloc(sizeof(bool) * len);
		g_prev[i] = (t_poi *)malloc(sizeof(t_poi) * len);
		j = 0;
		while (j < len)
		{
			g_visit[i][j] = NOT_VISITED;
			g_prev[i][j].x = -1;
			g_prev[i][j].y = -1;
			j++;
		}
		i++;
	}
	return ;
}


void	ft_putnbr(size_t n)
{
	int		temp;
	int		n_size;

	n_size = 1;
	temp = n;
	while ((temp /= 10))
		n_size = (n_size << 4) - (n_size << 2) - (n_size << 1);
	while (n_size > 0)
	{
		ft_putchar_fd(n / n_size + '0', 1);
		n %= n_size;
		n_size /= 10;
	}
}