#include "ft_ls.h"

int	process(int argc, char **argv)
{
  char *res;

  if (argc == 1)
    res = ".";
  while ( argc > 1 )
      ft_ls(argv[--argc]);
}

int	main(int argc, char **argv)
{
  process(argc, argv);
  return (0);
}
