/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 01:07:43 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/22 20:18:50 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <sys/ioctl.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdlib.h>
# include <stdio.h>
# include <grp.h>
# include <sys/stat.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <time.h>
# include <unistd.h>
# include <sys/xattr.h>

int	main()
{
	DIR 		*dir;
	struct 		dirent *dp;
	char *path = "main.c"; 

	dir = opendir(path);
	if (dir)
		while ((dp = readdir(dir)))
			printf("%s\n",dp->d_name);
	else
		printf("haha\n");
	//closedir(dir);
	return 0;
}
