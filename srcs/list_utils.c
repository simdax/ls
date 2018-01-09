/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:07:53 by simdax            #+#    #+#             */
/*   Updated: 2018/01/09 19:06:12 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	sort_f(t_list *el1, t_list *el2)
{
	t_node *one;
	t_node *two;

	one = el1->content;
	two = el2->content;
	return (ft_strcmp(two->name, one->name));
}

int	get_max_link(t_list *a, int val)
{
	t_node	*node;
	int		nb_link;

	node = a->content;
	nb_link = (int)node->sb.st_nlink;
	return (nb_link > val ? nb_link : val);
}

int	get_max_size(t_list *a, int val)
{
	t_node	*node;
	int		size;

	node = a->content;
	size = (int)node->sb.st_size;
	return (size > val ? size : val);
}

