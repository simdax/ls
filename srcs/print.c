#include "ft_ls.h"

void		print_stat(struct stat sb, void *flags)
{
  printf("%s\n", lsperms(sb.st_mode));
  //  printf("%c%c%c%c%c%c%c%c%c%c %d %s %s %d %s %s",

	/* switch (sb.st_mode & S_IFMT) { */
	/* case S_IFBLK:  printf("block device\n");            break; */
	/* case S_IFCHR:  printf("character device\n");        break; */
	/* case S_IFDIR:  printf("directory\n");               break; */
	/* case S_IFIFO:  printf("FIFO/pipe\n");               break; */
	/* case S_IFLNK:  printf("symlink\n");                 break; */
	/* case S_IFREG:  printf("regular file\n");            break; */
	/* case S_IFSOCK: printf("socket\n");                  break; */
	/* default:       printf("unknown?\n");                break; */
	/* } */
	/* printf("I-node number:            %ld", (long) sb.st_ino); */
	/* printf("Mode:                     %lo (octal)", */
	/* 	   (unsigned long) sb.st_mode); */
	/* printf("Link count:               %ld", (long) sb.st_nlink); */
	/* printf("Ownership:                UID=%ld   GID=%ld", */
	/* 	   (long) sb.st_uid, (long) sb.st_gid); */
	/* printf("Ownership Name:        	  %s", */
        /*        ft_strdup(getpwuid(sb.st_uid)->pw_name)); */
	/* printf("Group Name:        	  %s", */
        /*        ft_strdup(getgrgid(sb.st_gid)->gr_name)); */
	/* printf("Preferred I/O block size: %ld bytes", */
	/* 	   (long) sb.st_blksize); */
	/* printf("File size:                %lld bytes", */
	/* 	   (long long) sb.st_size); */
	/* printf("Blocks allocated:         %lld", */
	/* 	   (long long) sb.st_blocks); */
	/* printf("Last status change:       %s", ctime(&sb.st_ctime)); */
	/* printf("Last file access:         %s", ctime(&sb.st_atime)); */
	/* printf("Last file modification:   %s", ctime(&sb.st_mtime));   */
}

void		print(t_list *el, void *flags)
{
  char		*name;
  char		*fullname;
  struct stat	sb;

  sb = ((t_node*)el->content)->sb;
  name = ((t_node*)el->content)->name;
  fullname = ((t_node*)el->content)->fullname;
  printf("%s", name);
  /* printf("%d et %d %d %d %d ", ((int*)flags)[0], */
  /* 	   ((int*)flags)[1], ((int*)flags)[2], */
  /* 	   ((int*)flags)[3], ((int*)flags)[4] */
  /* 	); */
  print_stat(sb, flags);
  if (is_dir(sb.st_mode))
      read_dir(fullname, flags);
}
