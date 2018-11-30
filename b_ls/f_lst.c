/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_lst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 01:26:24 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/24 01:26:26 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_ls.h"

void	ft_lstappend(t_list **list_ref, void *data)
{
	t_list *head;

	if (*list_ref == NULL)
		*list_ref = ft_create_node(data);
	else
	{
		head = *list_ref;
		while (head->next != NULL)
			head = head->next;
		head->next = ft_create_node(data);	
	}
}

t_list	*ft_create_node(void *data)
{
	t_list	*node;

	if (!(node = (t_list *)p(sizeof(t_list))))
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}
/*
void	ft_print_lst(t_list **list_ref)
{
	t_list *head;

	head = NULL;
	if (*list_ref)
		head = *list_ref;
	else if (list_ref == NULL || *list_ref == NULL)
		return ;
	while (head)
	{
		printf("%s\n", head->data);
		head = head->next;
	}
}
*/

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

int 		ft_in_lst(t_list **target, void *data)
{
	t_list 	*head;

	head = *target;
	while (head)
	{
		if (ft_comptr((char *)head->data, (char *)data) == 0)
			return (1);
		head = head->next;
	}
	return (0);
}