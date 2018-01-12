/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 09:47:12 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/12 18:09:18 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		size_of_lst(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		++i;
	}
	return (i);
}

char		**array_from_list(t_list *lst)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	size = size_of_lst(lst);
	ret = (char**)malloc(sizeof(char*) * (size + 1));
	while (i < size)
	{
		ret[i] = ft_strdup(((t_node*)lst->content)->name);
		lst = lst->next;
		++i;
	}
	ret[size] = 0;
	return (ret);
}

char		*cat_filename(char *file1, char *file2)
{
	char	*ret;
	size_t	size;
	size_t	size1;

	size1 = ft_strlen(file1);
	size = size1 + ft_strlen(file2) + 1;
	ret = (char*)malloc(size + 1);
	ft_strcpy(ret, file1);
	if (file1[size1 - 1] != '/')
		ft_strcat(ret, "/");
	ft_strcat(ret, file2);
	return (ret);
}

struct stat	return_stat(char *file)
{
	struct stat sb;

	if (lstat(file, &sb) != 0)
	{
		printf("error %s  : ", file);
		perror("can't get stat of file");
		exit(errno);
	}
	return (sb);
}

int			is_dir(long st_mode)
{
	return (st_mode & S_IFMT) == S_IFDIR;
}

int			read_dir(char *file, void *flags)
{
	DIR			*dir;
	t_list		*list;

	if (!(dir = opendir(file)))
	{
		printf("%s : ", file);
		perror("erreur d'ouverture");
		exit(errno);
	}
	else
	{
		process(mkl_dir(dir, file), flags);
		closedir(dir);
		return (0);
	}
}
