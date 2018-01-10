/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:07:53 by simdax            #+#    #+#             */
/*   Updated: 2018/01/10 14:28:08 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_blkcnt(void* a, t_list *b)
{
	t_node		*node = b->content;

	*(blkcnt_t*)a += node->sb.st_blocks;
}

int		sort_f(t_list *el1, t_list *el2)
{
	t_node *one;
	t_node *two;

	one = el1->content;
	two = el2->content;
	return (!ft_strcmp(one->name, two->name));
}

int		sort_t(t_list *el1, t_list *el2)
{
	t_node *one;
	t_node *two;

	one = el1->content;
	two = el2->content;
	return (one->sb.st_ctime < two->sb.st_ctime);
}

int		get_max_link(t_list *a, int val)
{
	t_node	*node;
	int		nb_link;

	node = a->content;
	nb_link = (int)node->sb.st_nlink;
	return (nb_link > val ? nb_link : val);
}

int		get_max_size(t_list *a, int val)
{
	t_node	*node;
	int		size;

	node = a->content;
	size = (int)node->sb.st_size;
	return (size > val ? size : val);
}
