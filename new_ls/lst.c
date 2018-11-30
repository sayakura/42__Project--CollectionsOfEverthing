/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:46:03 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/10 17:46:03 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "b_ls.h"

t_list	*u_create_node(void *data)
{
	t_list	*node;

	if (!(node = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}

t_list	**u_create_lst(void)
{
	t_list	**lst;

	lst = (t_list **)malloc(sizeof(t_list *));
	*lst = NULL;
	return (lst);
}

void	u_lst_append(t_list **head_ref, void *data)
{
	t_list *new_node;
	t_list *last;

	last = *head_ref;
	new_node = u_create_node(data);
	if (*head_ref == NULL)
		*head_ref = new_node;
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
	}
}