/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:08:55 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/15 14:10:35 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t		size_of_lst(t_list *lst)
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

char		**array_from_list(t_list *lst, int all_flag)
{
	char	**ret;
	char	*name;
	int		size;
	int		i;

	i = 0;
	size = size_of_lst(lst);
	ret = (char**)malloc(sizeof(char*) * (size + 1));
	while (lst)
	{
		name = ((t_node*)lst->content)->name;
		if (!all_flag ? name[0] != '.' : 1)
		{
			ret[i] = ft_strdup(name);
			++i;
		}
		lst = lst->next;
	}
	ret[i] = 0;
	return (ret);
}
