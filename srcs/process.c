/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:32:54 by simdax            #+#    #+#             */
/*   Updated: 2018/01/08 18:16:25 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	process(t_list *list, void *f)
{
  int	*flags;
  int	sizes[2];
  
  flags = f;
  sizes[0] = ft_lstgetmax(list, 0, get_max_link);
  sizes[1] = ft_lstgetmax(list, 0, get_max_size);
  list = ft_lstsort(list, sort_f);
  ft_lstiter2(list, print, sizes);
  ft_lstdel(&list, clean);
}

void		print_stat(struct stat sb, void *flags)
{
  printf("%s %*d %s %s %*lld %s",
         lsperms(sb.st_mode),
         ft_nbrsize(((int*)flags)[0]),
         (int)sb.st_nlink,
         getpwuid(sb.st_uid)->pw_name,
         getgrgid(sb.st_gid)->gr_name,
         ft_nbrsize(((int*)flags)[1]),
         (long long) sb.st_size,
         ft_date(&sb.st_ctime)
  );
  fflush(stdout);
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
  /* printf("%d et %d %d %d %d ", ((int*)flags)[0], */
  /*    ((int*)flags)[1], ((int*)flags)[2], */
  /*    ((int*)flags)[3], ((int*)flags)[4] */
  /* ); */
  printf("%s\n", name);
  if (is_dir(sb.st_mode) &&
      ft_strcmp(".", name) &&
      ft_strcmp("..", name))
    read_dir(fullname, flags);
}
