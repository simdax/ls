/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:24:49 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/18 10:04:46 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		sort_f(t_list *el1, t_list *el2)
{
	t_node *one;
	t_node *two;

	one = el1->content;
	two = el2->content;
	return (ft_strcmp(one->name, two->name) < 0);
}

int		sort_t(t_list *el1, t_list *el2)
{
	t_node *one;
	t_node *two;

	one = el1->content;
	two = el2->content;
	if (one->sb.st_ctime == two->sb.st_ctime)
		return (ft_strcmp(one->name, two->name) < 0);
	return (one->sb.st_ctime > two->sb.st_ctime);
}

int		get_max_link(t_list *a, int val, void *flags)
{
	t_node	*node;
	int		nb_link;

	node = a->content;
	if (!((int*)flags)[ALL] && node->name[0] == '.')
		return (val);
	nb_link = node->sb.st_nlink;
	return (nb_link > val ? nb_link : val);
}

int		get_max_len(t_list *a, int val, void *flags)
{
	t_node	*node;
	int		len;

	node = a->content;
	if (!((int*)flags)[ALL] && node->name[0] == '.')
		return (val);
	len = ft_strlen(node->name);
	return (len > val ? len : val);
}

int		get_max_size(t_list *a, int val, void *flags)
{
	t_node	*node;
	int		size;

	node = a->content;
	if (!((int*)flags)[ALL] && node->name[0] == '.')
		return (val);
	size = (int)node->sb.st_size;
	return (size > val ? size : val);
}
