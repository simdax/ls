/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:38:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/15 17:30:06 by scornaz          ###   ########.fr       */
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

int			get_max(int argc, file_and_mode_t *argv)
{
	int len;
	int	max;
	int	i;

	max = 0;
	i = 0;
	while (i < argc)
	{
		len = ft_strlen((argv++)->name);
		max = len > max ? len : max;
		++i;
	}
	return (max + 8 - max % 8);
}

void		print_tab(int max, file_and_mode_t *blabla,
					  int cols, int space)
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
			printf("\e[%dm%-*s", get_color(blabla[j].mode), space, blabla[j].name);
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
	if (max)
		printf("\n");
	fflush(stdout);
}

void		p_print(int len, file_and_mode_t *array)
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
	file_and_mode_t	*array;
	
	array = array_from_list(list, all_flag);
	p_print(famlen(array), array);
	free(array);
	return (0);
}
