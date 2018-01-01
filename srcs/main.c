#include "ft_ls.h"

#define FLAGS "lrRat"
#define NB_FLAGS 5
  
typedef enum	e_flags
  {
    LONG, REVERSE, RECURSIVE, ALL, TIME_SORT
  }		t_flags;

int	process(int argc, char **argv)
{
  t_list	*list;
  t_node	node;
  
  list = 0;
  if (argc == 1)
    {
      ft_ls(".");
    }
  /* else */
  /*   while ( argc > 1 ) */
  /*     { */
  /*       node = (t_node){.stat = return_stat(".")}; */
  /*       ft_lstadd(&list, */
  /*                 ft_lstnew(&node, sizeof(t_node))); */
  /*     } */
}

void	take_flags(char **argv, int *arg)
{
  char 	*flags;
  char	*index;

  index = 0;
  flags = argv[1];
  if (flags && flags[0] == '-')
    {
      ++flags;
      while (*flags)
        {
          if ((index = strchr(FLAGS, *flags)))
            arg[index - FLAGS] = 1;
          ++flags;
        }
      ++(*argv);
    } 
}

int	main(int argc, char **argv)
{
  int	flags[NB_FLAGS];
                             
  ft_bzero(flags, sizeof(int) * NB_FLAGS);
  take_flags(argv, flags);
  process(argc, argv);
  return (0);
}
