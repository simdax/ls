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
  int		type;
  char		*name;
  struct stat	sb;
}		t_node;

struct stat	return_stat(char *file);
int		ft_ls(char *file);
int		read_dir(char *file);
void print_dirent(struct dirent *infos);
char		*cat_filename(char *file1, char *file2);
