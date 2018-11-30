/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_ls.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qpeng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 00:50:08 by qpeng             #+#    #+#             */
/*   Updated: 2018/09/24 01:06:21 by qpeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "f_ls.h"

extern uint8_t	g_flags;

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

char	*ft_getfpremi(int f_mod, const char *path)
{
	char	*ptr;
	size_t	index;
	int		arrow;
	char 	buf[1024];

	index = 1;
	arrow = 512;
	ptr = (char *)p(sizeof(char) * 12);
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


int 	ft_node_comptr(t_format *node, t_format *nex_nod)
{
	if (!(g_flags & f_r) && !(g_flags & f_t) &&\
						ft_comptr(node->fname, nex_nod->fname) > 0)
		return (1);
	else if ((g_flags & f_t) && ((g_flags & f_r) ?\
				node->time > nex_nod->time : node->time < nex_nod->time))
		return (1);
	else if ((g_flags & f_r) && !(g_flags & f_t) &&\
						ft_comptr(node->fname, nex_nod->fname) < 0)
		return (1);
	else 
		return (0);
}

void	ft_sortlst(t_list **list)
{
	t_list		*curr;
	t_format 	*node;
	t_format 	*nex_nod;

	curr = *list;

	while (curr->next != NULL)
	{
		node = (t_format *)(curr->data);
		nex_nod = (t_format *)(curr->next->data);
		if (ft_node_comptr(node, nex_nod))
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
	int 	len;
	char	*ptr;

	index = -1;
	while (ft_isalpha(*str))
		str++;
	while (!ft_isalpha(*str))
		str++;
	len = ft_strlen(str) - 9;
	ptr = (char *)p(sizeof(char) * len + 1);
	while (++index < len)
		ptr[index] = str[index];
 	ptr[index] = '\0';
 	return (ptr);
}

int 		ft_file_exsit(char *path)
{
	struct 		stat f_info;

	if (stat(path, &f_info) < 0)
	{
		printf("ls: %s: No such file or directory\n", path);
		return (0);
	}
	else
		return (1);
}

t_format	*ft_get_info(char *path)
{
	struct 		stat f_info;
	struct 		passwd *usr_i;
	struct 		group *grp_i;
	t_format	*cur_node;

	if (!(cur_node = (t_format *)p(sizeof(t_format))))
		return (NULL);
	if (stat(path, &f_info) < 0)
		return (NULL);
	usr_i = getpwuid(f_info.st_uid);
	grp_i = getgrgid(usr_i->pw_gid);
	cur_node->premi = ft_getfpremi(f_info.st_mode, path);;
	cur_node->links = f_info.st_nlink;
	cur_node->usrid =ft_strdup(usr_i->pw_name);
	cur_node->grpid = ft_strdup(grp_i->gr_name);
	cur_node->bytes = f_info.st_size;
	cur_node->time = f_info.st_mtime;
	cur_node->date = ft_strdup(ft_tformat(ctime(&f_info.st_ctime)));
	cur_node->fname = ft_strdup(path);
	return (cur_node);
}

t_dir 	*ft_getpath_info(char *path)
{
	DIR 		*dir;
	struct 		dirent *dp;
	t_list		**items_list;	
	t_dir		*dir_info;

	items_list = p(sizeof(t_list *));
	*items_list = NULL;
	dir_info = p(sizeof(t_dir));
	dir = opendir(path);
	if (dir)
	{
		dir_info->dirname = ft_strdup(path);
		while ((dp = readdir(dir)))
			ft_lstappend(items_list, ft_get_info(ft_add_prefix(path, dp->d_name)));
		closedir(dir);
	}
	ft_sortlst(items_list);
	dir_info->dirdata = items_list;
	return (dir_info);
}

t_list	**ft_getfiles_info(t_list **files_arg)
{
	t_list		**item_list;	
	t_list		*head;

	item_list = p(sizeof(t_list *));
	*item_list = NULL;
	head = *files_arg;
	while (head)
	{
		ft_lstappend(item_list, ft_get_info(head->data));
		head = head->next;
	}
	return (item_list);
}

t_list	**ft_getdirs_info(t_list **dirs_arg)
{
	t_list		**item_list;	
	t_list		*head;

	item_list = p(sizeof(t_list *));
	*item_list = NULL;
	head = *dirs_arg;
	while (head)
	{
		ft_lstappend(item_list, ft_getpath_info(head->data));
		head = head->next;
	}
	ft_sortlst(item_list);
	return (item_list);
}

t_args	*ft_get_args_info(t_list **files_arg)
{
	DIR 		*dir;
	t_list		*arg;
	t_args		*args;

	arg = *files_arg;
	args = p(sizeof(t_args));
	args->files = NULL;
	args->dirs = NULL;
	while (arg)
	{
		dir = opendir(arg->data);
		if (dir)
		{
			ft_lstappend(&(args->dirs), arg->data);
			closedir(dir);
		}
		else if (ft_file_exsit(arg->data))
			ft_lstappend(&(args->files), arg->data);
		arg = arg->next;
	}
	return (args);
}

size_t		*ft_print_formatted(t_list **list)
{
	t_list		*cur_node;
	size_t		*len;
	size_t 		count;
	t_format	*fmat_node;

	fmat_node = (t_format *)p(sizeof(t_format));
	count = 0;
	len = (size_t *)p(sizeof(size_t) * 5);
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
	return (len);
}

void	ft_print_items(t_list** files)
{
	t_list		*file;
	size_t		*len;
	t_format	*fmat_node;

	len = ft_print_formatted(files);
	file = *files;
	while (file)
	{
		fmat_node = (t_format *)file->data;
		if ((g_flags & f_a) == 0 &&\
			ft_get_basename((fmat_node->fname))[0] == '.')
		{
			file = file->next;
			continue ;
		}
		if (g_flags & f_l)
			printf("%s %s %s  %s  %s %s %s\n", fmat_node->premi,
				ft_adjustspaces(ft_lltoa(fmat_node->links, 10, 0), len[0]),
				ft_adjustspaces(fmat_node->usrid, len[1]),
				ft_adjustspaces(fmat_node->grpid, len[2]),
				ft_adjustspaces(ft_lltoa(fmat_node->bytes, 10, 0), len[3]),
				fmat_node->date, ft_get_basename(fmat_node->fname));
		else
			printf("%s\n", ft_get_basename(fmat_node->fname));
		file = file->next;
	}
}

void	ft_print_dirs(t_list **dirs, t_bool print_dir)
{
	t_list		*dir;
	t_dir		*dir_node;

	dir = *dirs;
	while (dir)
	{
		dir_node = (t_dir *)(dir->data);
		if (print_dir == 1 || dir->next)
			printf("%s:\n", dir_node->dirname);
		ft_print_items(dir_node->dirdata);
		if ((dir = dir->next))
			printf("\n");
		print_dir = 1;
	}
}

int	main(int ac, char **av)
{
	t_list	**files_arg;
	t_args	*args;
	t_bool 	print_dir;

	print_dir = 0;
	files_arg = ft_get_args(av);
	if (*files_arg)
	{
		args = ft_get_args_info(files_arg);
	
		if (args->files != NULL)
		{
			print_dir = 1;
			ft_print_items(ft_getfiles_info(&(args->files)));
		}
		if (args->dirs != NULL)
		{
			if (args->files != NULL)
				printf("\n");
			ft_print_dirs(ft_getdirs_info(&(args->dirs)), print_dir);
		}
	}
	else
		ft_print_items(ft_getpath_info(".")->dirdata);
	stop_the_world();
	return (0);
}