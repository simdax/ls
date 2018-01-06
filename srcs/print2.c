/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simdax </var/spool/mail/simdax>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 20:50:00 by simdax            #+#    #+#             */
/*   Updated: 2018/01/06 20:54:08 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int filetypeletter(int mode)
{
  char    c;

  if (S_ISREG(mode))
    c = '-';
  else if (S_ISDIR(mode))
    c = 'd';
  else if (S_ISBLK(mode))
    c = 'b';
  else if (S_ISCHR(mode))
    c = 'c';
#ifdef S_ISFIFO
  else if (S_ISFIFO(mode))
    c = 'p';
#endif  /* S_ISFIFO */
#ifdef S_ISLNK
  else if (S_ISLNK(mode))
    c = 'l';
#endif  /* S_ISLNK */
#ifdef S_ISSOCK
  else if (S_ISSOCK(mode))
    c = 's';
#endif  /* S_ISSOCK */
#ifdef S_ISDOOR
  /* Solaris 2.6, etc. */
  else if (S_ISDOOR(mode))
    c = 'D';
#endif  /* S_ISDOOR */
  else
    {
      /* Unknown type -- possibly a regular file? */
      c = '?';
    }
  return(c);
}

char	*lsperms(int mode)
{
  static const char *rwx[] = {"---", "--x", "-w-", "-wx",
                              "r--", "r-x", "rw-", "rwx"};
  static char bits[11];

  bits[0] = filetypeletter(mode);
  strcpy(&bits[1], rwx[(mode >> 6)& 7]);
  strcpy(&bits[4], rwx[(mode >> 3)& 7]);
  strcpy(&bits[7], rwx[(mode & 7)]);
  if (mode & S_ISUID)
    bits[3] = (mode & S_IXUSR) ? 's' : 'S';
  if (mode & S_ISGID)
    bits[6] = (mode & S_IXGRP) ? 's' : 'l';
  if (mode & S_ISVTX)
    bits[9] = (mode & S_IXOTH) ? 't' : 'T';
  bits[10] = '\0';
  return(bits);                          
}

