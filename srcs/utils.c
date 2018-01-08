/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 09:47:12 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/08 16:46:14 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*cat_filename(char *file1, char *file2)
{
	char	*ret;
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
      printf("error %s  : ", file);
      perror("can't get stat of file");
      exit(errno);
    }
	return (sb);
}

int		is_dir(long st_mode)
{
  return (st_mode & S_IFMT) == S_IFDIR;
}

int		read_dir(char *file, void *flags)
{
  DIR			*dir;
  t_list		*list;

  if (!(dir = opendir(file)))
    {
      printf("%s : ", file); fflush(stdout);
      perror("erreur d'ouverture");
      return (errno);
    }
  else
    {
      process(mkl_dir(dir, file), flags);
      closedir(dir);
      return (0);
    }
}
