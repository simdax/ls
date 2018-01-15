/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:38:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/15 15:08:25 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

unsigned	get_term_width(void)
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

int			get_max(int argc, char **argv)
{
	int len;
	int	max;
	int	i;

	max = 0;
	i = 0;
	while (i < argc)
	{
		len = ft_strlen(*argv++);
		max = len > max ? len : max;
		++i;
	}
	return (max + 8 - max % 8);
}

void		print_tab(int max, char **blabla, int cols, int space)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (i < max)
	{
		if (j < max)
		{
			printf("%-*s", space, blabla[j]);
			fflush(stdout);
			j += cols;
			++i;
		}
		else
		{
			printf("\n");
			fflush(stdout);
			j = ++k;
		}
	}
	printf("\n");
	fflush(stdout);
}

void		p_print(int len, char **array)
{
	int max;
	int width;
	int cols;

	max = get_max(len, array);
	width = get_term_width();
	print_tab(len, array, (len / (width / max)) + 1, max);
}

int			print_padded(t_list *list, int all_flag)
{
	char **array;

	array = array_from_list(list, all_flag);
	p_print(ft_strsplit_len(array), array);
	ft_free_strsplit(array);
	return (0);
}
