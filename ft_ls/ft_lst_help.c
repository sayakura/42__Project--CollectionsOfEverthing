/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_help.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/22 00:22:58 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/22 00:23:02 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_headers.h"

const char 	*g_flags;
char		*g_f;
size_t		g_len;

void	ft_sortbytime(t_list **list)
{
	t_list		*curr;
	t_format 	*node;
	t_format 	*nex_nod;

	curr = *list;

	while (curr->next != NULL)
	{
		node = (t_format *)(curr->data);
		nex_nod = (t_format *)(curr->next->data);
		if (node->time < nex_nod->time)
		{
			node = curr->next->data;
			curr->next->data = curr->data;
			curr->data = node;
			curr = *list;
		}
		else
			curr = curr->next;
	}
}

void	ft_sortlst(t_list **list)
{
	t_list		*curr;
	t_format 	*node;
	t_format 	*nex_nod;

	curr = *list;

	while (curr->next != NULL)
	{
		node = !ft_if_contain(g_f, 'r', g_len) ? (t_format *)(curr->data) :\
							(t_format *)(curr->next->data);
		nex_nod = !ft_if_contain(g_f, 'r', g_len) ? (t_format *)\
			(curr->next->data) : (t_format *)(curr->data);
		if (ft_comptr(node->fname, nex_nod->fname) > 0)
		{
			node = curr->next->data;
			curr->next->data = curr->data;
			curr->data = node;
			curr = *list;
		}
		else
			curr = curr->next;
	}
}