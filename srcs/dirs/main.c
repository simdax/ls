/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:38:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/15 11:12:02 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned get_term_width(void)
{
	int max_x;
	int max_y;

	initscr();
	getmaxyx(stdscr, max_y, max_x);
	endwin();
	if (max_x == -1)
    {
		fprintf(stderr, "getmaxyx() failed\n");
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
		++sizes;
    }
	return (max + 8 - max % 8);
}

void print_tab(int max, char **blabla, int cols, int space)
{
	int		i = 0;
	int		j = 0;
	int		k = 0;

	while (i < max)
	{
		if (j < max)
		{
			printf("%-*s", space, blabla[j]);
			j += cols;
			++i;
		}
		else
		{
			printf("\n");
			j = ++k;
		}
	}
	printf("\n");
}

 void		p_print(int argc, char **argv)
{
	int max;
	int width;
	int cols;
	
	++argv; --argc;
	max = get_max(argc, argv);
	width = get_term_width();
	print_tab(argc, argv, (argc / (width / max)) + 1, max);
}

int		print_padded(t_list *list)
{
	char **array;
	
	array = array_from_list(list);
	p_print(size_of_lst(list), array);
	return (0);
}
