/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 14:08:55 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/15 17:42:10 by scornaz          ###   ########.fr       */
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

int					famlen(file_and_mode_t *str)
{
	int	i;

	i = 0;
	while ((str++)->mode)
		++i;
	return (i);
}

void			free_fam(file_and_mode_t *fam)
{	
	file_and_mode_t	*cpy;

	cpy = fam;
	while (fam->mode)
		free((fam++)->name);
	free(cpy);
}

file_and_mode_t		*array_from_list(t_list *lst, int all_flag)
{
	file_and_mode_t	*ret;
	char			*name;
	int				mode;
	int				size;
	int				i;

	i = 0;
	size = size_of_lst(lst);
	ret = malloc(sizeof(*ret) * (size + 1));
	while (lst)
	{
		name = ((t_node*)lst->content)->name;
		mode = ((t_node*)lst->content)->sb.st_mode;
		if (!all_flag ? name[0] != '.' : 1)
		{
			ret[i].name = ft_strdup(name);
			ret[i].mode = mode;
			++i;
		}
		lst = lst->next;
	}
	ret[i].mode = 0;
	return (ret);
}
