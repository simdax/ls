#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>
#include "libft/libft.h"
#include "libft/list/includes.h"

typedef struct	s_node
{
  char		*name;
  char		*fullname;
  struct stat	sb;
}		t_node;

char		*lsperms(int mode);
int		is_dir(long st_mode);
void		clean(void *el, size_t len);
t_list 		*make_list(char **argv);
t_list		*mkl(DIR *dir, char *file);
void		print_stat(struct stat sb, void *flags);
t_node		return_node(char *parent, char* filename);
struct stat	return_stat(char *file);
int		ft_ls(t_list *lst);
 void		print(t_list *el, void *flags);
void		print_stat(struct stat sb, void *flags);
int		read_dir(char *file, void *flags);
void		print_dirent(struct dirent *infos);
char		*cat_filename(char *file1, char *file2);
