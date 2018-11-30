/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 17:45:36 by qpeng             #+#    #+#             */
/*   Updated: 2018/10/10 17:45:36 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef F_LS_H

# define F_LS_H

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
# include <stdint.h>
# include <stdbool.h>

# define ABS(a) (a < 0) ? -a : a

enum	e_flags
{
	SUCESS = 1,
	FAILED = 0,
	f_l = 1 << 0,
	f_a = 1 << 1,
	f_r = 1 << 2,
	f_t = 1 << 3,
};

typedef uint8_t	t_bool;


typedef struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;


typedef struct 		s_format
{
	char			*premi;
	size_t			links;
	char			*usrid;
	char			*grpid;
	long long		bytes;
	char			*date;
	char			*fname;
	long 			time;
}					t_format;

typedef struct 		s_args
{
	t_list			*f_args;
	t_list			*d_args;
}					t_args;

typedef struct 		s_dir
{
	char			*dirname;
	struct 	s_list 	**dirdata;
}					t_dir;

void	u_lst_append(t_list **head_ref, void *data);
t_list	**ft_get_args(char **av);
t_list	**u_create_lst(void);
#endif