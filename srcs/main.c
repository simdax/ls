/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 09:52:51 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/08 16:43:14 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define FLAGS "lrRat"
#define NB_FLAGS 5

typedef enum	e_flags
  {
    LONG, REVERSE, RECURSIVE, ALL, TIME_SORT
  }		t_flags;

void	take_flags(char **argv, int *arg)
{
  char	*flags;
  char	*index;

  index = 0;
  flags = argv[0];
  if (flags && flags[0] == '-')
    {
      ++flags;
      while (*flags)
        {
          if ((index = strchr(FLAGS, *flags)))
            arg[index - FLAGS] = 1;
          else
            {
              perror("flags error");
              exit(errno);
            }
          ++flags;
        }
      ++(*argv);
    }
}

int	main(int argc, char **argv)
{
  int		*flags;
  t_list	*list;

  flags = (int*)malloc(sizeof(int) * NB_FLAGS);
  ft_bzero(flags, sizeof(int) * NB_FLAGS);
  ++argv;
  take_flags(argv, flags);
  if (argc == 1)
    read_dir(".", flags);
  else
    process(mkl_argv(argv), flags);
  free(flags);
  return (0);
}
