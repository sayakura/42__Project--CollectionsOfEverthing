/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_ls.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:54:48 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/24 01:29:03 by qpeng            ###   ########.fr       */
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

# define ABS(a) (a < 0) ? -a : a

enum	e_flags
{
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
	struct	s_list	*files;
	struct	s_list	*dirs;
}					t_args;

typedef struct 		s_dir
{
	char			*dirname;
	struct 	s_list 	**dirdata;
}					t_dir;

void				ft_lstappend(t_list **list_ref, void *data);
t_list				*ft_create_node(void *data);
void				ft_save_flags(char *str);
t_list				**ft_get_args(char **av);
void				*p(size_t data_siz);
void				initial_arr(size_t *arr, size_t size);
size_t				ft_numlen(size_t num);
void				append_ptr(t_list *ptr);
t_list				*create_ptr(void *data);
void				stop_the_world(void);
void				ft_print_lst(t_list **list_ref);
char				*ft_add_prefix(char *path, char *basename);
int 				ft_in_lst(t_list **target, void *data);
char    			*ft_get_basename(const char *str);
uint8_t				ft_strlen(const char* str);
char   				*ft_strdup(const char *str);
int					ft_isalpha(int c);
int 				ft_comptr(char *s1, char *s2);
char				*ft_adjustspaces(char *str, size_t max);
char				*ft_lltoa(long long num, int base, signed char isupper);
#endif
