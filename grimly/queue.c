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
	this->maxSize = size + 1;
	this->tail = 0;
	this->head = 1;
	this->listArray = (int *)malloc(sizeof(int) * this->maxSize);
	this->isEmpty = true;
}

void	f_queue_enqueue(int it, t_queue *this)
{
	if (((this->tail + 2) % this->maxSize) != this->head)
	{
		this->tail = (this->tail + 1) % this->maxSize;
		this->listArray[this->tail] = it;
		this->isEmpty = false;
	}
}

int		f_queue_dequeue(t_queue *this)
{
	int		length;
	int		it;

	length = ((this->tail + this->maxSize) -\
		this->head + 1) % this->maxSize;
	if(length != 0)
	{
		it = this->listArray[this->head];
		this->head = (this->head + 1) % this->maxSize;
		length = ((this->tail + this->maxSize) -\
			this->head + 1) % this->maxSize;
		this->isEmpty = (length == 0) ? true : false;
		return it;
	}
	return (INT_MAX);
}
/*
int		f_queue_front(t_queue *this)
{
	return (this->listArray[this->head]);	
}
*/