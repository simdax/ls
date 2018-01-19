/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:06:29 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/19 15:06:59 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static unsigned	get_term_width(void)
{
	int max_x;
	int max_y;

	initscr();
	getmaxyx(stdscr, max_y, max_x);
	endwin();
	if (max_x == -1)
	{
		ft_printf("getmaxyx() failed\n");
		return (0);
	}
	return (max_x);
}

static int		get_max(int argc, t_node **argv)
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

static void		print_tab(t_padding_args args, t_node **blabla, int *flags)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (i < args.max)
	{
		if (j < args.max)
		{
			ft_printf("\e[%dm%-*s%s\e[37m",
					flags[COLOR] ? get_color(blabla[j]->sb) : 37,
					args.space, blabla[j]->name, flags[COLOR] ? "\e[37m" : "");
			j += args.cols;
			++i;
		}
		else
		{
			write(1, "\n", 1);
			j = ++k;
		}
	}
	if (args.max)
		write(1, "\n", 1);
}

static void		p_print(int len, t_node **array, int *flags)
{
	t_padding_args	args;
	int				max;
	int				width;

	max = get_max(len, array);
	width = get_term_width();
	args.max = len;
	args.cols = max > width ? len : (len / (width / max)) + 1;
	args.space = max;
	print_tab(args, array, flags);
}

int				print_padded(t_list *list, int *flags)
{
	t_node	**array;

	array = array_from_list(list, flags[ALL]);
	p_print(famlen(array), array, flags);
	free(array);
	return (0);
}
