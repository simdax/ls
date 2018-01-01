#include "ft_ls.h"

#define FLAGS "lrRat"
#define NB_FLAGS 5

typedef enum	e_flags
  {
    LONG, REVERSE, RECURSIVE, ALL, TIME_SORT
  }		t_flags;


t_list	*make_list(char **argv)
{
  t_node	node;
  t_list	*list;

  list = 0;
  while (*argv)
    {
      node = return_node(".", *argv);
      ft_lstadd(&list,
                ft_lstnew(&node, sizeof(t_node)));
      ++argv;
    }
  return (list);
}

int	process(int argc, char **argv, int *flags)
{
  t_list	*list;
  t_node	node;
  char		*def[2];

  def[0] = ".\0";
  def[1] = 0;
  list = 0;
  if (argc == 1)
    list = make_list(def);
  else
    list = make_list(argv);
  ft_lstiter2(list, print, flags);
}

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
          ++flags;
        }
      ++(*argv);
    }
}

int	main(int argc, char **argv)
{
  int	*flags;

  flags = (int*)malloc(sizeof(int) * NB_FLAGS);
  ft_bzero(flags, sizeof(int) * NB_FLAGS);
  ++argv;
  take_flags(argv, flags);
  process(argc, argv, flags);
  free(flags);
  return (0);
}
