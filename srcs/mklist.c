/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mklist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:26:29 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/12 17:20:32 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list		*mkl_dir(DIR *dir, char *file)
{
	struct dirent	*dir_inf;
	t_list			*list;
	t_node			node;

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
	t_list	*tmp;
	
	list = 0;
	while (*argv)
	{
		node.name = ft_strdup(*argv);
		node.fullname = ft_strdup(*argv);
		node.sb = return_stat(node.fullname);
		tmp = ft_lstnew(&node, sizeof(t_node));
		if (!tmp)
			clean(&node, sizeof(node));
		ft_lstadd(&list, tmp);
		++argv;
	}
	return (list);
}

void		clean(void *el, size_t len)
{
	t_node *e;

	e = el;
	free(e->name);
	e->name = NULL;
	free(e->fullname);
	e->fullname = NULL;
	ft_bzero(el, len);
	free(e);
}
