#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned get_term_width( void ) {
  int max_x;
  int max_y;

  initscr();
  getmaxyx( stdscr, max_y, max_x );
  endwin();
  if ( max_x == -1 )
    {
      fprintf( stderr, "getmaxyx() failed\n" );
      return (0);
    }
  return (max_x);
}

int	get_max(int argc, char **argv)
{
  int	*sizes;
  int	max;
  int	cumul;
  
  max = 0;
  cumul = 0;
  sizes = (int*)malloc(sizeof(int) * argc + 1);
  sizes[argc] = -1;
  while (--argc >= 0)
      sizes[argc] = strlen(*argv++);
  while (*sizes != -1)
    {
      max = *sizes > max ? *sizes : max;
      //cumul += *sizes + *sizes % 4;
      //      printf("%d\n", cumul);
      ++sizes;
    }
  return (max);
}

void	print_padded(char **blabla, int max, int width)
{
  int cumul;

  cumul = 0;
  while (*blabla)
    {
      cumul += strlen(*blabla);
      printf("%s\t", *blabla);
      if (cumul > max)
        {
          cumul = 0;
          printf("\n");
        }
      ++blabla;
    }  
}

int main(int argc, char **argv)
{
  ++argv; --argc;
  print_padded(argv, get_max(argc, argv), get_term_width());
}
