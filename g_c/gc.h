/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 23:17:46 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/22 00:13:51 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_H

# define GC_H
# include <stdlib.h>

typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;
void				*p(size_t data_siz);
void				append_ptr(t_list *ptr);
t_list				*create_ptr(void *data);
void				stop_the_world(void);
#endif
