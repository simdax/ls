#include "ft_ls.h"

void print_dirent(struct dirent *infos)
{
  printf("inode : %d\n", infos->d_ino);
  if (infos->d_type == DT_DIR)
    printf("type : dir\n");
  else if (infos->d_type == DT_REG)
    printf("type : file\n");
  else if (infos->d_type == DT_LNK)
    printf("type : link\n");
  printf("name : %s\n", infos->d_name);
}

int		read_dir(char *file)
{
  DIR  		*dir;
  struct dirent	*dir_inf;

  if (!(dir = opendir(file)))
    {
      perror("erreur d'ouverture");
      return (errno);
    }
  else
    {
      while (dir_inf = readdir(dir))
        print_dirent(dir_inf);
      closedir(dir);
      return (0);
    }  
}

int		ft_ls(char *file)
{
  struct stat sb;
  
  if (stat(file, &sb) == 1)
    {
      perror("can't get stat of file");
      return (errno);
    }

  printf("File type:                ");
  switch (sb.st_mode & S_IFMT) {
  case S_IFBLK:  printf("block device\n");            break;
  case S_IFCHR:  printf("character device\n");        break;
  case S_IFDIR:  printf("directory\n");               break;
  case S_IFIFO:  printf("FIFO/pipe\n");               break;
  case S_IFLNK:  printf("symlink\n");                 break;
  case S_IFREG:  printf("regular file\n");            break;
  case S_IFSOCK: printf("socket\n");                  break;
  default:       printf("unknown?\n");                break;
  }
  printf("I-node number:            %ld\n", (long) sb.st_ino);
  printf("Mode:                     %lo (octal)\n",
         (unsigned long) sb.st_mode);
  printf("Link count:               %ld\n", (long) sb.st_nlink);
  printf("Ownership:                UID=%ld   GID=%ld\n",
         (long) sb.st_uid, (long) sb.st_gid);
  printf("Preferred I/O block size: %ld bytes\n",
         (long) sb.st_blksize);
  printf("File size:                %lld bytes\n",
         (long long) sb.st_size);
  printf("Blocks allocated:         %lld\n",
         (long long) sb.st_blocks);
  printf("Last status change:       %s", ctime(&sb.st_ctime));
  printf("Last file access:         %s", ctime(&sb.st_atime));
  printf("Last file modification:   %s", ctime(&sb.st_mtime));
}
