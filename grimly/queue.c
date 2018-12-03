/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 23:35:41 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/25 23:35:41 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	f_queue_init(size_t size, t_queue *this)
{
	this->max_size = size + 1;
	this->tail = 0;
	this->head = 1;
	this->list_array = (int *)malloc(sizeof(int) * this->max_size);
	this->is_empty = TRUE;
}

void	f_queue_enqueue(int it, t_queue *this)
{
	if (((this->tail + 2) % this->max_size) != this->head)
	{
		this->tail = (this->tail + 1) % this->max_size;
		this->list_array[this->tail] = it;
		this->is_empty = FALSE;
	}
}

int		f_queue_dequeue(t_queue *this)
{
	int		length;
	int		it;

	length = ((this->tail + this->max_size) -\
	this->head + 1) % this->max_size;
	if (length != 0)
	{
		it = this->list_array[this->head];
		this->head = (this->head + 1) % this->max_size;
		length = ((this->tail + this->max_size) -\
			this->head + 1) % this->max_size;
		this->is_empty = (length == 0) ? TRUE : FALSE;
		return (it);
	}
	return (INT_MAX);
}
