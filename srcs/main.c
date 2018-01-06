/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 09:52:51 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/06 12:50:00 by simdax           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	process(int argc, char **argv, int *flags)
{
	t_list	*list;
	t_node	node;
	char		*def;

	def = strdup(".");
	list = 0;
	if (argc == 1)
		list = make_list(&def);
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
			else
			{
                          perror("flags error");
                            exit(errno);
			}
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
