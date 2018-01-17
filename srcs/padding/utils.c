/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:08:55 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/17 13:42:11 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t				size_of_lst(t_list *lst)
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

int					famlen(t_node **str)
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

t_node		**array_from_list(t_list *lst, int all_flag)
{
	t_node		**ret;
	char		*name;
	int			mode;
	int			size;
	int			i;

	i = 0;
	size = size_of_lst(lst);
	ret = (t_node**)malloc(sizeof(*ret) * (size + 1));
	while (lst)
	{
		if (!all_flag ? ((t_node*)(lst->content))->name[0] != '.' : 1)
		{
			ret[i] = (t_node*)lst->content;
			++i;
		}
		lst = lst->next;
	}
	ret[i] = 0;
	return (ret);
}
