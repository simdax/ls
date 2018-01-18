/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 09:52:51 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/18 13:52:54 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	parse_f(char *flags, int *arg)
{
	char	*index;

	index = 0;
	while (*flags)
	{
		if ((index = ft_strchr(FLAGS_LS, *flags)))
				arg[index - FLAGS_LS] = 1;
		else
		{
			ft_printf("Flags error: usage %s\n", FLAGS_LS);
			exit(1);
		}
		++flags;
	}
}

int		take_flags(char ***p_argv, int *argc, int *arg)
{
	char	*flags;
	char	**argv;

	argv = *p_argv;
	flags = argv[0];
	if (flags && flags[0] == '-')
	{
		if (ft_strcmp(flags, "--"))
		{
			++flags;
			parse_f(flags, arg);
			++(*p_argv);
			--(*argc);
			return (1);
		}
		else
		{
			++(*p_argv);
			--(*argc);
			return (0);			
		}
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int		*flags;
	t_list	*list;

	--argc;
	flags = (int*)malloc(sizeof(int) * NB_FLAGS);
	ft_bzero(flags, sizeof(int) * NB_FLAGS);
	++argv;
	while (take_flags(&argv, &argc, flags))
		;
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
