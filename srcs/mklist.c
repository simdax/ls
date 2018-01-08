/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mklist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 19:01:25 by simdax            #+#    #+#             */
/*   Updated: 2018/01/08 16:44:29 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*mkl_dir(DIR *dir, char *file)
{
  struct dirent	*dir_inf;
  t_list	*list;
  t_node	 node;

  list = 0;
  while ((dir_inf = readdir(dir)))
    {
      node.name = ft_strdup(dir_inf->d_name);
      node.fullname = cat_filename(file, node.name);
      node.sb = return_stat(node.fullname);
      ft_lstadd(&list, ft_lstnew(&node, sizeof(t_node)));
    }
  return (list);
}

t_list		*mkl_argv(char **argv)
{
  t_node	node;
  t_list	*list;
        
  list = 0;
  while (*argv)
    {
      node.name = ft_strdup(*argv);
      node.fullname = ft_strdup(*argv);
      node.sb = return_stat(node.fullname);
      ft_lstadd(&list, ft_lstnew(&node, sizeof(t_node)));
      ++argv;
    }
  return (list);
}

void		clean(void *el, size_t len)
{
  t_node *e = (t_node*)el;

  free(e->name);
  e->name = NULL;
  free(e->fullname);
  e->fullname = NULL;
  ft_bzero(el, len);
}
