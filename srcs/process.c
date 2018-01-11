/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:30:43 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/11 17:03:17 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	g_first = 0;

static void	r_dir(char **dirs, int *flags, int blk_size)
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
		{
			printf("%s:\n", *dirs);
			fflush(stdout);
		}
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
		if (!flags[ALL] && name[0] == '.')
			return (0);
		if (!ft_strcmp(name, fullname))
			return (1);
		return (flags[RECURSIVE] && ft_strcmp(name, ".") && ft_strcmp(name, ".."));
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
	else
		printf("%s\n", name);
	fflush(stdout);
}

static void		init_infos(t_infos *infos, t_list *list, int *flags)
{
	infos->block_size = 0;
	infos->dirs = malloc(sizeof(char*) * 1000);
	infos->dirs[0] = "";
	infos->max_inodes = ft_lstgetmax(list, 0, get_max_link);
	infos->max_sizes = ft_lstgetmax(list, 0, get_max_size);
	ft_lstreduce(list, get_blkcnt, &(infos->block_size));
	infos->flags = flags;	
}

void		process(t_list *list, void *p_flags)
{
	t_infos	infos;
	int		*flags;
	t_list	*tmp_list;

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
		ft_lstdel(&tmp_list, clean);
	}
	if (flags[LONG] && !flags[ALONE])
		printf("total %d\n", infos.block_size);
	fflush(stdout);
	ft_lstiter2(list, print, &infos);
	r_dir(infos.dirs, flags, infos.block_size);
	ft_lstdel(&list, clean);
}
