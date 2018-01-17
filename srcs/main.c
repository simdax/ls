/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 09:52:51 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/17 16:36:38 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	take_flags(char ***p_argv, int *argc, int *arg)
{
	char	*flags;
	char	*index;
	char	**argv;

	argv = *p_argv;
	index = 0;
	flags = argv[0];
	if (flags && flags[0] == '-')
	{
		++flags;
		while (*flags)
		{
			if ((index = ft_strchr(FLAGS_LS, *flags)))
				arg[index - FLAGS_LS] = 1;
			else
			{
				ft_printf("Flags error: usage %s", FLAGS_LS);
				exit(1);
			}
			++flags;
		}
		++(*p_argv);
		--(*argc);
	}
}

int		main(int argc, char **argv)
{
	int		*flags;
	t_list	*list;

	--argc;
	flags = (int*)malloc(sizeof(int) * NB_FLAGS);
	ft_bzero(flags, sizeof(int) * NB_FLAGS);
	++argv;
	take_flags(&argv, &argc, flags);
	if (!argc)
	{
		*(--argv) = ".";
		++argc;
	}
	if (argc == 1)
		flags[ALONE] = 1;
	process(mkl_argv(argv), flags);
	free(flags);
	return (0);
}
