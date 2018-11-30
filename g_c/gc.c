/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 23:00:04 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/22 00:13:13 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"

t_list	**g_p_lst;

void	*p(size_t data_siz)
{
	void	*ptr;

	ptr = malloc(data_siz);
	append_ptr(create_ptr(ptr));
	return (ptr);
}

void	append_ptr(t_list *ptr)
{
	t_list	*head;

	if (g_p_lst == NULL || *g_p_lst == NULL)
	{
		g_p_lst = (t_list **)malloc(sizeof(t_list *));
		*g_p_lst = ptr;
	}
	else
	{
		head = *g_p_lst;
		while (head->next)
			head = head->next;
		head->next = ptr;
	}
}

t_list	*create_ptr(void *data)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	ptr->data = data;
	ptr->next = NULL;
	return (ptr);
}

void	stop_the_world(void)
{
	t_list	*head;
	t_list	*next;

	head = *g_p_lst;
	while (head)
	{
		next = head->next;
		free(head->data);
		free(head);
		head = next;
	}
	free(g_p_lst);
}
