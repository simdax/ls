/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:38:34 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/17 16:02:33 by scornaz          ###   ########.fr       */
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

int			get_max(int argc, t_node **argv)
{
	int len;
	int	max;
	int	i;

	max = 0;
	i = 0;
	while (i < argc)
	{
		len = ft_strlen((*argv++)->name);
		max = len > max ? len : max;
		++i;
	}
	return (max + 8 - max % 8);
}

void		print_tab(int max, t_node **blabla, int cols, int space)
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
			ft_printf("\e[%dm%-*s\e[37m", get_color(blabla[j]->sb),
				   space, blabla[j]->name);
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

void		p_print(int len, t_node **array)
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
	t_node	**array;
	
	array = array_from_list(list, all_flag);
	p_print(famlen(array), array);
	free(array);
	return (0);
}
