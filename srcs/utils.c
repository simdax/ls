/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 09:47:12 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/16 11:05:44 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_blkcnt(void *a, t_list *b, void *flags)
{
	t_node		*node;

	node = b->content;
	if (!((int*)flags)[ALL] && node->name[0] == '.')
		return ;
	*(blkcnt_t*)a += node->sb.st_blocks;
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

int			return_stat(char *file, struct stat *sb)
{
	if (lstat(file, sb) != 0)
	{
		ft_printf("error %s  : ", file);
		perror("can't get stat of file");
		return (0);
	}
	return (1);
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
		ft_printf("oups, %s : ", file);
		perror("erreur d'ouverture");
		return (0);
	}
	else
	{
		process(mkl_dir(dir, file), flags);
		closedir(dir);
		return (1);
	}
}
