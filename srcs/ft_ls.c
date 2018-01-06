/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 09:47:12 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/06 12:52:29 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*cat_filename(char *file1, char *file2)
{
	char		*ret;
	size_t	size;

	size = ft_strlen(file1) + ft_strlen(file2) + 1;
	ret = (char*)malloc(size + 1);
	ft_strcpy(ret, file1);
	ft_strcat(ret, "/");
	ft_strcat(ret, file2);
	return (ret);
}

struct stat	return_stat(char *file)
{
	struct stat sb;
  
	if (lstat(file, &sb) != 0)
    {
		perror("can't get stat of file");
		exit(errno);
    }
	return (sb);
}

t_node		return_node(char *parent, char* filename)
{
	char *tmp_name;
  
	tmp_name = cat_filename(parent, filename);
	return (t_node){ft_strdup(parent), ft_strdup(filename),
			return_stat(tmp_name)};
}
