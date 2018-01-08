/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:32:54 by simdax            #+#    #+#             */
/*   Updated: 2018/01/08 16:33:08 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_stat(struct stat sb, void *flags)
{
  printf("%s %d %s %s %lld %s",
         lsperms(sb.st_mode),
         (int)sb.st_nlink,
         getpwuid(sb.st_uid)->pw_name,
         getgrgid(sb.st_gid)->gr_name,
         (long long) sb.st_size,
         ctime(&sb.st_ctime)
  );
}

void		print(t_list *el, void *flags)
{
  char		*name;
  char		*fullname;
  struct stat	sb;

  sb = ((t_node*)el->content)->sb;
  name = ((t_node*)el->content)->name;
  fullname = ((t_node*)el->content)->fullname;
  print_stat(sb, flags);
  printf("%s\n", name);
  /* printf("%d et %d %d %d %d ", ((int*)flags)[0], */
  /*    ((int*)flags)[1], ((int*)flags)[2], */
  /*    ((int*)flags)[3], ((int*)flags)[4] */
  /* ); */
  if (is_dir(sb.st_mode) &&
      ft_strcmp(".", name) &&
      ft_strcmp("..", name))
    read_dir(fullname, flags);
}
