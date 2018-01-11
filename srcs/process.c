/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:30:43 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/11 13:42:59 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	r_dir(char **dirs, int *flags)
{
	int		i;
	char	**cpy;

	i = 0;
	while (ft_strcmp(*dirs, ""))
	{
		/* if (flags[REVERSE]) */
		/* { */
		/* 	write(1, "\n", 1); */
		/* 	read_dir(*dirs, flags); */
		/* } */
		--dirs;
		++i;
	}
	cpy = dirs;
	if (!flags[REVERSE])
		while (--i >= 0)
		{
			write(1, "\n", 1);
			read_dir(*(++dirs), flags);
		}
	free(cpy);
}

int			recur(int ret, long mode, char *name, char *fullname)
{
	if (is_dir(mode))
	{
		if (!ft_strcmp(name, fullname))
			return (1);
		return (ret && ft_strcmp(name, ".") && ft_strcmp(name, ".."));
	}
	return (0);
}

void		print(t_list *el, void *p_read)
{
	char		*name;
	char		*fullname;
	struct stat	sb;
	t_infos		*infos;

	infos = (t_infos*)p_read;
	sb = ((t_node*)el->content)->sb;
	name = ((t_node*)el->content)->name;
	fullname = ((t_node*)el->content)->fullname;
	if (recur(infos->flags[RECURSIVE], sb.st_mode, name, fullname))
	{
		infos->dirs += 1;
		infos->dirs[0] = fullname;
	}
	if ((!ft_strcmp(name, fullname) && is_dir(sb.st_mode)) ||
		(!infos->flags[ALL] && name[0] == '.'))
		return ;
	if (infos->flags[LONG])
	{
		print_stat(sb, infos);
	}
	printf("%s\n", name);
	fflush(stdout);
}

void		process(t_list *list, void *p_flags)
{
	int		sizes[2];
	t_infos	infos;
	int		*flags;

	flags = p_flags;
	infos.block_size = 0;
	infos.dirs = malloc(sizeof(char*) * 1000);
	infos.dirs[0] = "";
	infos.max_inodes = ft_lstgetmax(list, 0, get_max_link);
	infos.max_sizes = ft_lstgetmax(list, 0, get_max_size);
	ft_lstreduce(list, get_blkcnt, &infos.block_size);
	infos.flags = flags;
	if (flags[TIME_SORT])
		list = ft_lstsort(list, sort_t);
	else
		list = ft_lstsort(list, sort_f);
	ft_lstiter2(list, print, &infos);
	r_dir(infos.dirs, flags);
	ft_lstdel(&list, clean);
}
