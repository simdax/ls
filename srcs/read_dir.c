/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 14:32:45 by simdax            #+#    #+#             */
/*   Updated: 2018/01/06 19:09:22 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
      list = mkl(dir, file);
      //sort();
      closedir(dir);
      ft_lstiter2(list, print, flags);
      ft_lstdel(&list, clean);
      return (0);
    }
}
