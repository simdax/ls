/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:08:55 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/18 17:04:37 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t			size_of_lst(t_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		++i;
	}
	return (i);
}

int				famlen(t_node **str)
{
	int	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

void			free_fam(t_node **fam)
{
	t_node	**cpy;

	cpy = fam;
	while (*fam)
		free((*fam++)->name);
	free(cpy);
}

t_node			**array_from_list(t_list *lst, int all_flag)
{
	t_node		**ret;
	t_node		*node;
	int			mode;
	int			size;
	int			i;

	i = 0;
	size = size_of_lst(lst);
	ret = (t_node**)malloc(sizeof(*ret) * (size + 1));
	while (lst)
	{
		node = lst->content;
		if ((ft_strcmp(node->name, node->fullname) &&
			 !is_dir(node->sb.st_mode)) ||
			(all_flag && node->name[0] == '.'))
		{
			ret[i] = node;
			++i;
		}
		lst = lst->next;
	}
	ret[i] = 0;
	return (ret);
}
