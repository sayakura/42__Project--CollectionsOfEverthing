/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 07:29:25 by qpeng             #+#    #+#             */
/*   Updated: 2018/12/06 07:30:12 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/fillit.h"

short       next_block(uint32_t bits, int length)
{
    int     index;
    int     one;

    one = 1UL;
    index = 0;
    while (length--)
    {
        if ((bits & one) == 0)
            return (index);
        one <<= 1;
        index++;
    }
    return (42);
} 

uint32_t    fill_bit(int length)
{
    uint32_t    bits;
    int         one;

    bits = 0;
    one = 1;
    while (length--)
    {
        bits |= one;
        one <<= 1;
    }
    return (bits);
}