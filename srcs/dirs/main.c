/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:38:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/12 18:10:26 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

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

void		print_padded(int argc, char **argv)
{
	int max;
	int width;
	int cols;
	
	++argv; --argc;
	max = get_max(argc, argv);
	width = get_term_width();
	print_tab(argc, argv, (argc / (width / max)) + 1, max);
}
