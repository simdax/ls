/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:07:00 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/18 11:00:52 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	g_first = 0;

static void		r_dir(char **dirs, int *flags, int blk_size)
{
	int		i;
	char	**cpy;

	i = 0;
	while (ft_strcmp(*dirs, ""))
	{
		--dirs;
		++i;
	}
	cpy = dirs;
	while (--i >= 0)
	{
		++dirs;
		if (g_first)
			write(1, "\n", 1);
		else
			g_first = 1;
		if (!flags[ALONE])
			ft_printf("%s:\n", *dirs);
		else
			flags[ALONE] = 0;
		read_dir(*dirs, flags);
	}
	free(cpy);
}

static int		recur(int *flags, long mode, char *name, char *fullname)
{
	if (is_dir(mode))
	{
		if (!ft_strcmp(name, fullname))
			return (1);
		if (!flags[ALL] && name[0] == '.')
			return (0);
		return (flags[RECURSIVE] && ft_strcmp(name, ".")
				&& ft_strcmp(name, ".."));
	}
	return (0);
}

void			print(t_list *el, void *p_read)
{
	char		*name;
	char		*fullname;
	struct stat	sb;
	t_infos		*infos;

	infos = (t_infos*)p_read;
	ft_memcpy(&sb, &((t_node*)el->content)->sb, sizeof(struct stat));
	name = ((t_node*)el->content)->name;
	fullname = ((t_node*)el->content)->fullname;
	if (recur(infos->flags, sb.st_mode, name, fullname))
	{
		infos->dirs += 1;
		infos->dirs[0] = fullname;
	}
	if ((!ft_strcmp(name, fullname) && is_dir(sb.st_mode)) ||
		(!infos->flags[ALL] && name[0] == '.'))
		return ;
	if (infos->flags[LONG])
		print_stat(sb, name, fullname, infos);
}

static void		init_infos(t_infos *infos, t_list *list, int *flags)
{
	infos->block_size = 0;
	infos->dirs = malloc(sizeof(char*) * 1000000);
	infos->dirs[0] = "";
	infos->max_inodes = ft_lstgetmax(list, 0, get_max_link, flags);
	infos->max_sizes = ft_lstgetmax(list, 0, get_max_size, flags);
	infos->max_len = ft_lstgetmax(list, 0, get_max_len, flags);
	ft_lstreduce(list, get_blkcnt, &(infos->block_size), flags);
	infos->flags = flags;
}

void			process(t_list *list, void *p_flags)
{
	t_infos	infos;
	int		*flags;
	t_list	*tmp_list;

	tmp_list = 0;
	flags = p_flags;
	init_infos(&infos, list, flags);
	if (flags[TIME_SORT])
		list = ft_lstsort(list, sort_t);
	else
		list = ft_lstsort(list, sort_f);
	if (flags[REVERSE])
	{
		tmp_list = list;
		list = ft_cpyrev(list);
	}
	if (flags[LONG] && !flags[ALONE])
		ft_printf("total %d\n", infos.block_size);
	ft_lstiter2(list, print, &infos);
	if (!flags[LONG] && !flags[ALONE])
		print_padded(list, flags);
	r_dir(infos.dirs, flags, infos.block_size);
	ft_lstdel(&list, clean);
}
