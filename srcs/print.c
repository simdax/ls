/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 15:25:55 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/15 15:10:01 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_stat(struct stat sb, char *name,
						char *fullname, t_infos *infos)
{
	char *smlink;

	smlink = malloc(1000);
	if (S_ISLNK(sb.st_mode))
		readlink(fullname, smlink, 1000);
	else
	{
		free(smlink);
		smlink = 0;
	}
	printf("%s%c%*d %s  %s  %*lld%s%s%s%s\n",
			lsperms(sb.st_mode),
			' ',
			(int)ft_nbrsize(infos->max_inodes) + 1,
			(int)sb.st_nlink,
			getpwuid(sb.st_uid)->pw_name,
			getgrgid(sb.st_gid)->gr_name,
			(int)ft_nbrsize(infos->max_sizes),
			(long long)sb.st_size,
			ft_date(&sb.st_ctime),
			name,
			S_ISLNK(sb.st_mode) ? " -> " : "",
			smlink ? smlink : "");
	fflush(stdout);
	free(smlink);
}

int			filetypeletter(int mode)
{
	char	c;

	if (S_ISREG(mode))
		c = '-';
	else if (S_ISDIR(mode))
		c = 'd';
	else if (S_ISBLK(mode))
		c = 'b';
	else if (S_ISCHR(mode))
		c = 'c';
	else if (S_ISFIFO(mode))
		c = 'p';
	else if (S_ISLNK(mode))
		c = 'l';
	else if (S_ISSOCK(mode))
		c = 's';
	else
		c = '?';
	return (c);
}

char		*lsperms(int mode)
{
	static const	char *rwx[] = {"---", "--x", "-w-", "-wx",
		"r--", "r-x", "rw-", "rwx"};
	static			char bits[11];

	bits[0] = filetypeletter(mode);
	ft_strcpy(&bits[1], rwx[(mode >> 6) & 7]);
	ft_strcpy(&bits[4], rwx[(mode >> 3) & 7]);
	ft_strcpy(&bits[7], rwx[(mode & 7)]);
	if (mode & S_ISUID)
		bits[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		bits[6] = (mode & S_IXGRP) ? 's' : 'l';
	if (mode & S_ISVTX)
		bits[9] = (mode & S_IXOTH) ? 't' : 'T';
	bits[10] = '\0';
	return (bits);
}

char		*ft_date(void *time)
{
	static char	ret[14];

	ft_strncpy(ret, ctime(time) + 3, 13);
	ret[13] = ' ';
	return (ret);
}
