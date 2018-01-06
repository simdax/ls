/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mklist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 19:01:25 by simdax            #+#    #+#             */
/*   Updated: 2018/01/06 19:51:08 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*mkl(DIR *dir, char *file)
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
      if (ft_strcmp(".", dir_inf->d_name) && ft_strcmp("..", dir_inf->d_name))
        ft_lstadd(&list, ft_lstnew(&node, sizeof(t_node)));
    }
  return (list);
}

t_list	*make_list(char **argv)
{
	t_node	node;
	t_list	*list;
        
	list = 0;
	while (*argv)
    {
      node.name = ft_strdup(*argv);
      node.fullname = node.name;
      node.sb = return_stat(node.fullname);
      /* if (is_dir(node.sb.st_mode) && */
      /*     !ft_strchr("./", node.name[0])) */
      /*     node.fullname = cat_filename(".", node.name); */
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
