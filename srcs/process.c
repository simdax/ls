/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:30:43 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/10 17:42:52 by scornaz          ###   ########.fr       */
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
		--dirs;
		++i;
	}
	cpy = dirs;
	while (--i >= 0)
	{
		write(1, "\n", 1);
		read_dir(*(++dirs), flags);
	}
	free(cpy);
}

void		print_stat(struct stat sb, void *flags)
{
	printf("%s  %*d %s  %s  %*lld%s",
			lsperms(sb.st_mode),
			(int)ft_nbrsize(((int*)flags)[0]),
			(int)sb.st_nlink,
			getpwuid(sb.st_uid)->pw_name,
			getgrgid(sb.st_gid)->gr_name,
			(int)ft_nbrsize(((int*)flags)[1]),
			(long long)sb.st_size,
			ft_date(&sb.st_ctime));
	fflush(stdout);
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
	t_f			*read;

	read = (t_f*)p_read;
	sb = ((t_node*)el->content)->sb;
	name = ((t_node*)el->content)->name;
	fullname = ((t_node*)el->content)->fullname;
	if (recur(read->flags[RECURSIVE], sb.st_mode, name, fullname))
	{
		read->dirs += 1;
		read->dirs[0] = fullname;
	}
	if ((!ft_strcmp(name, fullname) && is_dir(sb.st_mode)) ||
		(!read->flags[ALL] && name[0] == '.'))
		return ;
	if (read->flags[LONG])
		print_stat(sb, read->sizes);
	printf("%s\n", name);
	fflush(stdout);
}

void		process(t_list *list, void *p_flags)
{
	int	sizes[2];
	t_f	read;
	int block_size;
	int	*flags;

	flags = p_flags;
	block_size = 0;
	read.dirs = malloc(sizeof(char*) * 1000);
	read.dirs[0] = "";
	read.sizes[0] = ft_lstgetmax(list, 0, get_max_link);
	read.sizes[1] = ft_lstgetmax(list, 0, get_max_size);
	read.flags = flags;
	ft_lstreduce(list, get_blkcnt, &block_size);
	if (flags[ALL])
		printf("total %d\n", block_size);
	if (flags[TIME_SORT])
		list = ft_lstsort(list, sort_t);
	else if (flags[REVERSE])
		list = ft_lstsort(list, sort_r);
	else
		list = ft_lstsort(list, sort_f);
	ft_lstiter2(list, print, &read);
	r_dir(read.dirs, flags);
	ft_lstdel(&list, clean);
}
