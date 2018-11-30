/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 01:43:57 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/20 01:43:59 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_headers.h"

const char 	*g_flags = "lart";

size_t		g_len = 0;
char		*g_f;
long long	g_size = 0;
char 		has_args = 0;

char		ft_check_flag_valid(char *av)
{
	size_t			index;
	size_t			j;
	unsigned char	_matched;

	j = 0;
	index = 0;
	if (av[0] != '-')
		return (0);
	if (av[1] == '\0')
		return (-41);
	av++;
	while (av[index])
	{
		j = 0;
		_matched = 0;
		while (g_flags[j])
		{
			if (av[index] == g_flags[j])
			{
				_matched = 1;
				break ;
			}
			j++;
		}
		if (!_matched)
			return (av[index]);
		index++;
	}
	return (-42);
}

void	ft_save_flags(char *av)
{
	size_t	index;
	size_t	len;

	len = 0;
	index = 0;
	while (av[index])
	{
		if (ft_if_contain(av, av[index], index))
		{
			index++;
			continue ;
		}
		len++;
		index++;
	}
	index = 0;
	len = 0;
	while (av[len])
	{
		if (ft_if_contain(av, av[len], len))
		{
			len++;
			continue ;
		}
		g_f[g_len++] = av[len++];
	}
}

void	ft_sortbytime(t_list **list)
{
	t_list		*curr;
	t_format 	*node;
	t_format 	*nex_nod;

	curr = *list;

	while (curr->next != NULL)
	{
		node = (t_format *)(curr->data);
		nex_nod = (t_format *)(curr->next->data);
		if (node->time < nex_nod->time)
		{
			node = curr->next->data;
			curr->next->data = curr->data;
			curr->data = node;
			curr = *list;
		}
		else
			curr = curr->next;
	}
}

void	ft_sortlst(t_list **list)
{
	t_list		*curr;
	t_format 	*node;
	t_format 	*nex_nod;

	curr = *list;

	while (curr->next != NULL)
	{
		node = !ft_if_contain(g_f, 'r', g_len) ? (t_format *)(curr->data) :\
							(t_format *)(curr->next->data);
		nex_nod = !ft_if_contain(g_f, 'r', g_len) ? (t_format *)\
			(curr->next->data) : (t_format *)(curr->data);
		if (ft_comptr(node->fname, nex_nod->fname) > 0)
		{
			node = curr->next->data;
			curr->next->data = curr->data;
			curr->data = node;
			curr = *list;
		}
		else
			curr = curr->next;
	}
}

char	*ft_tformat(const char *str)
{
	int		index;
	size_t	len;
	char	*ptr;

	index = -1;
	while (ft_isalpha(*str))
		str++;
	while (!ft_isalpha(*str))
		str++;
	len = ft_strlen(str) - 9;
	ptr = (char *)malloc(sizeof(char) * len + 1);
	while (++index < len)
		ptr[index] = str[index];
 	ptr[index] = '\0';
 	return (ptr);
}

char	*ft_getfpremi(int	f_mod, const char *path)
{
	char	*ptr;
	size_t	index;
	int		arrow;
	char 	buf[1024];

	index = 1;
	arrow = 512;
	ptr = (char *)malloc(sizeof(char) * 12);
	if (S_ISDIR(f_mod))
		ptr[0] = 'd';
	else if (S_ISLNK(f_mod))
		ptr[0] = 'l';
	else if (S_ISSOCK(f_mod))
		ptr[0] = 's';
	else if (S_ISCHR(f_mod))
		ptr[0] = 'c';
	else if (S_ISBLK(f_mod))
		ptr[0] = 'b';
	else
		ptr[0] = '-';
	while (arrow >>= 1)
		if (f_mod & arrow)
			if (index % 3 == 1)
				ptr[index++] = 'r';
			else if(index % 3 == 2)
				ptr[index++] = 'w';
			else
				ptr[index++] = 'x';
		else
			ptr[index++] = '-';
	if (listxattr(path, buf, 1024, 1) > 0)
		ptr[10] = '@';
	else
		ptr[10] = ' ';
	ptr[11] = '\0';
	return (ptr);
}

t_format	*ft_get_row_info(char *path)
{
	struct 		stat f_info;
	struct 		passwd *usr_i;
	struct 		group *grp_i;
	t_format	*cur_node;
	char		*ptr;

	if (!(cur_node = (t_format *)malloc(sizeof(t_format))))
		return (NULL);
	if (stat(path, &f_info) < 0)
		return (NULL);
	usr_i = getpwuid(f_info.st_uid);
	grp_i = getgrgid(usr_i->pw_gid);
	ptr = ft_getfpremi(f_info.st_mode, path);
	cur_node->premi = ptr;
	cur_node->links = f_info.st_nlink;
	ptr = ft_strdup(usr_i->pw_name);
	cur_node->usrid = ptr;
	ptr = ft_strdup(grp_i->gr_name);
	cur_node->grpid = ptr;
	cur_node->bytes = f_info.st_size;
	cur_node->time = f_info.st_ctime;
	ptr = ft_strdup(ft_tformat(ctime(&f_info.st_ctime)));
	cur_node->date = ptr;
	ptr = ft_strdup(path);
	cur_node->fname =ptr;
	if (!ft_if_contain(g_f, 'a', g_len) && ptr[0] != '.')
		g_size += f_info.st_size;
	else if (ft_if_contain(g_f, 'a', g_len))
		g_size += f_info.st_size;
	return (cur_node);

}

int 	ft_skip(t_format *fmat_node)
{
	if (!ft_if_contain(g_f, 'a', g_len) && (fmat_node->fname)[0] == '.')
		return (1);
	else if (has_args == 1 && (fmat_node->premi)[0] == 'd' )
		return (1);
	else if (has_args == 2  && (fmat_node->premi)[0] == '-')
		return (1);
	else
		return (0);
}

void	ft_printer(t_list *cur_node, size_t *len)
{
	size_t		count;
	t_format	*fmat_node;

	fmat_node = (t_format *)malloc(sizeof(t_format));
	if (ft_if_contain(g_f, 'l', g_len) && has_args == 0)
		printf("total %lld\n", g_size / 496);
	while (cur_node)
	{
		fmat_node = (t_format *)cur_node->data;
		if (ft_skip(fmat_node))
		{
			cur_node = cur_node->next;
			continue ;
		}
		else if (ft_if_contain(g_f, 'l', g_len))
		{
			printf("%s %s %s  %s  %s %s %s\n", fmat_node->premi,
				ft_adjustspaces(ft_lltoa(fmat_node->links, 10, 0), len[0]),
				ft_adjustspaces(fmat_node->usrid, len[1]),
				ft_adjustspaces(fmat_node->grpid, len[2]),
				ft_adjustspaces(ft_lltoa(fmat_node->bytes, 10, 0), len[3]),
				fmat_node->date, fmat_node->fname);
		}
		else
			printf("%s\n", fmat_node->fname);
		cur_node = cur_node->next;
	}
}

void	ft_cur_print(t_list *cur_node, size_t *len)
{
	size_t		count;
	t_format	*fmat_node;
	t_list		**item_lst;
	t_list 		*head;
	size_t		*len2;

	fmat_node = (t_format *)malloc(sizeof(t_format));
	while (cur_node)
	{
		fmat_node = (t_format *)cur_node->data;
		if (ft_skip(fmat_node))
		{
			cur_node = cur_node->next;
			continue ;
		}
		else
		{
			printf("%s:\n", fmat_node->fname);
			item_lst = ft_getdir_itemlst(fmat_node->fname, NULL);
			ft_sortlst(item_lst);
			while (*item_lst)
			{
				fmat_node = (t_format *)((*item_lst)->data);
				if (!ft_if_contain(g_f, 'a', g_len) && ft_get_filename(fmat_node->fname)[0] == '.')
				{
					*item_lst = (*item_lst)->next;
					continue ;
				}
				else if (ft_if_contain(g_f, 'l', g_len))
				{
					printf("%s %s %s  %s  %s %s %s\n", fmat_node->premi,
						ft_adjustspaces(ft_lltoa(fmat_node->links, 10, 0), len[0]),
						ft_adjustspaces(fmat_node->usrid, len[1]),
						ft_adjustspaces(fmat_node->grpid, len[2]),
						ft_adjustspaces(ft_lltoa(fmat_node->bytes, 10, 0), len[3]),
						fmat_node->date, ft_get_filename(fmat_node->fname));
				}
				else
					printf("%s\n", ft_get_filename(fmat_node->fname));
				*item_lst = (*item_lst)->next;
			}
		}
		printf("\n");
		cur_node = cur_node->next;
	}
}

void	ft_print_help(t_list *cur_node, size_t *len)
{
	
	ft_printer(cur_node, len);
	if (has_args == 1)
	{
		printf("\n");
		has_args = 2;
		ft_cur_print(cur_node, len); 
	}
}

size_t		*ft_print_formatted(t_list **list)
{
	t_list		*cur_node;
	size_t		*len;
	size_t 		count;
	t_format	*fmat_node;

	fmat_node = (t_format *)malloc(sizeof(t_format));
	count = 0;
	len = (size_t *)malloc(sizeof(size_t) * 5);
	initial_arr(len, 5);
	cur_node = *list;
	while (cur_node)
	{
		fmat_node = (t_format *)cur_node->data;
		if (ft_numlen(fmat_node->links) > len[0])
			len[0] = ft_numlen(fmat_node->links) ;
		if (ft_strlen(fmat_node->usrid) > len[1])
			len[1] = ft_strlen(fmat_node->usrid);
		if (ft_strlen(fmat_node->grpid) > len[2])
			len[2] = ft_strlen(fmat_node->grpid);
		if (ft_numlen(fmat_node->bytes) > len[3])
			len[3] = ft_numlen(fmat_node->bytes);
		cur_node = cur_node->next;
	}
	ft_sortlst(list);
	if (ft_if_contain(g_f, 't', g_len))
		ft_sortbytime(list);
	return (len);
}


t_list	**ft_getdir_itemlst(char *path, t_list **file_list)
{
	DIR 		*dir;
	struct 		dirent *dp;
	t_list		**item_list;	

	item_list = (t_list **)malloc(sizeof(t_list *));
	*item_list = NULL;
	dir = opendir(path);
	if (dir)
	{
		while ((dp = readdir(dir)))
		{
			if (file_list != NULL && ft_if_in_lst(file_list, dp->d_name))
				ft_lstappend(item_list, ft_get_row_info(ft_strpre(path, dp->d_name)));
			else if (file_list == NULL)
				ft_lstappend(item_list,  ft_get_row_info(ft_strpre(path, dp->d_name)));
		}
	}
	closedir(dir);
	return (item_list);
}

t_list	**ft_load_flags(int ac, char **av)
{
	size_t	index;
	char	flag;
	t_list	**item_lst;

	index = 0;
	item_lst = (t_list **)malloc(sizeof(t_list *));
	*item_lst = NULL;
	while (index < ac - 1)
	{
		if ((flag = ft_check_flag_valid(av[index])) == -42)
			ft_save_flags(av[index] + 1);
		else
		{
			has_args = 1;
			ft_lstappend(item_lst, av[index]);
		}
		index++;
	}
	return (item_lst);
}

int 	ft_is_dir(char *path)
{
	DIR 		*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	else
		return (0);
}

t_ls	*ft_get_ls(t_list **args)
{
	t_list	**files;
	t_list	**dirs;
	t_ls 	*ls;
	t_list 	*head;

	files = (t_list **)malloc(sizeof(t_list *));
	*files = NULL;
	dirs = (t_list **)malloc(sizeof(t_list *));
	*dirs = NULL;
	ls = (t_ls *)malloc(sizeof(t_ls));
	while (*args)
	{
		if (ft_is_dir((*args)->data))
			ft_lstappend(dirs, (*args)->data);
		else
			ft_lstappend(files, (*args)->data);
		*args = (*args)->next;
	}
	ls->files = files;
	ls->dirs = dirs;
	return (ls);
}

int		main(int ac, char **av)
{

	char	flag;
	t_list	**item_lst;
	t_ls 	*ls;

	g_f = (char *)malloc(sizeof(char) * 10);
	g_f[9] = '\0';
	if (ac < 2)
	{
		item_lst = ft_getdir_itemlst(".", NULL);
		ft_print_help(*item_lst, ft_print_formatted(item_lst));
	}
	else
	{
		item_lst = ft_load_flags(ac, ++av);
		if (has_args)
		{
		
			ls = ft_get_ls(item_lst);
			item_lst = ft_getdir_itemlst(".", ls->files);
			//ft_print_help(*item_lst, ft_print_formatted(item_lst));
		}
		else
		{
			item_lst = ft_getdir_itemlst(".", NULL);
			ft_print_help(*item_lst, ft_print_formatted(item_lst));
		}
		/*
		flag = ft_check_flag_valid(av[1]);
		if (flag == -42)
		{
			ft_save_flags(++av[1]);
			ft_getdir_itemlst();
		}
		else if (flag == -41)
			write(1, "ls: -: No such file or directory\n", 33);
		else
		{
			write(2, "ls: illegal option -- ", 22);
			write(2, &flag, 1);
			write(2, "\nusage: ls [-ABCFGHLOPRSTUWabc", 31);
			write(2, "defghiklmnopqrstuwx1] [file ...]\n", 34);
		}*/
	}
	return (0);
}