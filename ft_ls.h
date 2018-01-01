#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include "libft/libft.h"

typedef struct	s_node
{
  char		*parent;
  char		*name;
  struct stat	sb;
}		t_node;

t_node		return_node(char *parent, char* filename);
struct stat	return_stat(char *file);
int		ft_ls(t_list *lst);
void		print(t_list *el);
void		print_stat(struct stat sb);
int		read_dir(char *file);
void		print_dirent(struct dirent *infos);
char		*cat_filename(char *file1, char *file2);
