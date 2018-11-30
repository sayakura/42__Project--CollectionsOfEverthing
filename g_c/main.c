/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 23:26:04 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/22 00:09:03 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc.h"
#include <stdio.h>


int		main(void)
{
	char	*ptr;
	char	*ptr2;
	char	**ptr3;

	ptr2 = p(sizeof(char) * 2);
	ptr2[0] = 'A';
	ptr2[1] = '\0';

 	ptr = p(sizeof(char) * 2);
	ptr[0] = 'B';
	ptr[1] = '\0';

	ptr3 = p(sizeof(char *));
	*ptr3 = ptr2;
	printf("%s\n", ptr);
	printf("%s\n", ptr2);
	printf("%s\n", *ptr3);
	stop_the_world();
	printf("%s\n", *ptr3);
	printf("%s\n", ptr);
	printf("%s\n", ptr2);
	return (0);
}
