/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_headers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 02:58:14 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/22 20:39:50 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HEADERS_H

# define FT_HEADERS_H

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

# define ABS(a) (a < 0) ? -a : a

typedef struct 		s_list
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

typedef struct		s_ls
{
	t_list			**files;
	t_list			**dirs;
}					t_ls;

char				*ft_strpre(char *str1, char *str2);
size_t				*ft_print_formatted(t_list **list);
void				ft_print_help(t_list *cur_node, size_t *len);
char    			*ft_adjustspaces(char *str, size_t max);
char    			*ft_lltoa(long long num, int base, signed char isupper);
int					ft_isalpha(char c);
size_t				ft_strlen(const char* str);
void				ft_lstappend(t_list **list, void  *node);
t_list				**ft_getdir_itemlst(char *path, t_list **file_list);
void				ft_printer(t_list *cur_node, size_t *len);
void				initial_arr(size_t *arr, size_t size);
char    			*ft_strdup(const char *str);
t_list				*ft_get_c_item(void *data, size_t content_size);
size_t				ft_numlen(size_t num);
int 				ft_comptr(char *s1, char *s2);
int 				ft_if_contain(char *arr, char flag, size_t n);
void	ft_display_current_d(char *path);
char				*ft_add_space_end(char *str, size_t max);
void				ft_sortlst(t_list **list);
void				ft_sortbytime(t_list **list);
int 		ft_if_in_lst(t_list **target_list, void *data);
char    *ft_get_filename(char *path);

void	ft_sortbytime(t_list **list);
void	ft_sortlst(t_list **list);
#endif
