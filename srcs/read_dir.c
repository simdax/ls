/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/01 14:32:45 by simdax            #+#    #+#             */
/*   Updated: 2018/01/01 14:33:10 by simdax           ###   ########.fr       */
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

void		print(t_list *el)
{
  char	*name;
  char	*parent_name;
  char	*tmp_name;
  int	type;

  type = ((t_node*)el->content)->type;
  parent_name = ((t_node*)el->content)->parent;
  name = ((t_node*)el->content)->name;
  write(1, name, strlen(name));
  write(1, "\n", 1);
  if ( type == DT_DIR &&
       (strcmp("..", name)) &&
       (strcmp(".", name)))
    {
      tmp_name = cat_filename(parent_name, name);
      read_dir(tmp_name);
      free(tmp_name);
    }
}

int		read_dir(char *file)
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
          node = (t_node){file, dir_inf->d_type,
                          strdup(dir_inf->d_name),
                          return_stat(dir_inf->d_name)
          };
          ft_lstadd(&list,
                    ft_lstnew(&node, sizeof(t_node)));
        }
      closedir(dir);
      ft_lstiter(list, print);
      return (0);
    }
}
