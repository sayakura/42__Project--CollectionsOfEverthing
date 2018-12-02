/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 23:35:57 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/25 23:35:57 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef QUEUE_H
# define QUEUE_H

# define queue(funct) f_queue_##funct

void	f_queue_init(size_t size, t_queue *this);
void	f_queue_enqueue(int	it, t_queue *this);
int		f_queue_dequeue(t_queue *this);
int		f_queue_front(t_queue *this);

# endif