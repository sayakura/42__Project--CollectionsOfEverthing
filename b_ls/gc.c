/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 23:00:04 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/24 01:55:50 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_ls.h"

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

	if (g_p_lst == NULL)
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

	if (g_p_lst == NULL || *g_p_lst == NULL)
		return ;
	head = *g_p_lst;
	while (head)
	{
		next = head->next;/*
		if (head->data != NULL)
			free(head->data);*/
		if (head != NULL)
			free(head);
		head = next;
	}
	if (g_p_lst)
		free(g_p_lst);
}
