/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 14:32:45 by simdax            #+#    #+#             */
/*   Updated: 2018/01/01 17:03:44 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char		*cat_filename(char *file1, char *file2)
{
  char		*ret;
  size_t	size;

  size = strlen(file1) + strlen(file2) + 1;
  ret = (char*)malloc(size + 1);
  strcpy(ret, file1);
  strcat(ret, "/");
  strcat(ret, file2);
  return (ret);
}

int		nb_args(DIR *dir)
{
  int res;

  res = 0;
  while (readdir(dir))
      ++res;
  return (res);
}

void		print(t_list *el, void *flags)
{
  char		*name;
  char		*parent_name;
  char		*tmp_name;
  struct stat	sb;

  sb = ((t_node*)el->content)->sb;
  parent_name = ((t_node*)el->content)->parent;
  name = ((t_node*)el->content)->name;
  printf("%s\n", name);
  printf("%d et %d %d %d \n", ((int*)flags)[0],
	 ((int*)flags)[1], ((int*)flags)[2],
	 ((int*)flags)[3], ((int*)flags)[4]
	 );
  print_stat(sb);
  if ( (sb.st_mode & S_IFMT) == S_IFDIR &&
	(strcmp("..", name)) &&
	(strcmp(".", name))
       )
    {
      tmp_name = cat_filename(parent_name, name);
      read_dir(tmp_name, flags);
      free(tmp_name);
    }
}

int		read_dir(char *file, void *flags)
{
  DIR		*dir;
  struct dirent	*dir_inf;
  t_list	*list;
  t_node	node;

  list = NULL;
  if (!(dir = opendir(file)))
    {
      printf("%s : ", file); fflush(stdout);
      perror("erreur d'ouverture ");
      return (errno);
    }
  else
    {
      while (dir_inf = readdir(dir))
        {
          node = return_node(file, dir_inf->d_name);
          ft_lstadd(&list,
                    ft_lstnew(&node, sizeof(t_node)));
        }
      closedir(dir);
      ft_lstiter2(list, print, flags);
      return (0);
    }
}
