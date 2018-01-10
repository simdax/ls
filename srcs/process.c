/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 16:32:54 by simdax            #+#    #+#             */
/*   Updated: 2018/01/10 14:11:08 by scornaz          ###   ########.fr       */
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

void	process(t_list *list, void *f)
{
	int	*flags;
	int	sizes[2];
	t_f	read;
	int block_size;

	block_size = 0;
	flags = f;
	read.dirs = malloc(sizeof(char*) * 1000);
	read.dirs[0] = "";
	read.sizes[0] = ft_lstgetmax(list, 0, get_max_link);
	read.sizes[1] = ft_lstgetmax(list, 0, get_max_size);
	ft_lstreduce(list, get_blkcnt, &block_size);
	printf("total %d\n", block_size);
	list = ft_lstsort(list, sort_t);
	ft_lstiter2(list, print, &read);
	r_dir(read.dirs, flags);
	ft_lstdel(&list, clean);
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
		   (long long) sb.st_size,
		   ft_date(&sb.st_ctime)
		);
	fflush(stdout);
}

void		print(t_list *el, void *flags)
{
	char		*name;
	char		*fullname;
	struct stat	sb;
	
	sb = ((t_node*)el->content)->sb;
	name = ((t_node*)el->content)->name;
	fullname = ((t_node*)el->content)->fullname;
	print_stat(sb, ((t_f*)flags)->sizes);
	printf("%s\n", name);
	fflush(stdout);
	if (is_dir(sb.st_mode) &&
		ft_strcmp(".", name) &&
		ft_strcmp("..", name))
	{
		((t_f*)flags)->dirs += 1;
		((t_f*)flags)->dirs[0] = fullname;
	}
}
