/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 11:20:09 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/10 14:11:54 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <time.h>
# include <string.h>
# include <grp.h>
# include <pwd.h>
# include "libft.h"
# include "libft/list/includes.h"

# define FLAGS "lrRat"
# define NB_FLAGS 5

typedef struct	s_node
{
  char			*name;
  char			*fullname;
  struct stat	sb;
}		t_node;

typedef struct	s_f
{
	int		sizes[2];
	char	**dirs;
}			t_f;

typedef enum	e_flags
{
    LONG, REVERSE, RECURSIVE, ALL, TIME_SORT
}				t_flags;

void		get_blkcnt(void* a, t_list *b);
int			sort_f(t_list *el1, t_list *el2);
int			sort_t(t_list *el1, t_list *el2);
int			get_max_link(t_list *a, int val);
int			get_max_size(t_list *a, int val);
void		process(t_list *list, void *f);
char		*lsperms(int mode);
char		*ft_date(void *time);
int			is_dir(long st_mode);
void		clean(void *el, size_t len);
t_list 		*mkl_argv(char **argv);
t_list		*mkl_dir(DIR *dir, char *file);
void		print_stat(struct stat sb, void *flags);
t_node		return_node(char *parent, char* filename);
struct stat	return_stat(char *file);
int			ft_ls(t_list *lst);
 void		print(t_list *el, void *flags);
void		print_stat(struct stat sb, void *flags);
int			read_dir(char *file, void *flags);
void		print_dirent(struct dirent *infos);
char		*cat_filename(char *file1, char *file2);

#endif
