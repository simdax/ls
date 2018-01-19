/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 09:52:51 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/19 15:03:41 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		parse_f(char *flags, int *arg)
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

int				take_flags(char ***p_argv, int *argc, int *arg)
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

static int		all_invisible(char **argv)
{
	int	ret;

	ret = 0;
	while (*argv)
	{
		ret += ft_strcmp(".", *argv) + ft_strcmp("..", *argv);
		++argv;
	}
	return (ret != 0);
}

static char		**solve_link(int len, char **argv)
{
	struct stat	sb;
	char		**ret;
	int			i;

	i = 0;
	ret = (char**)malloc(sizeof(char*) * (len + 1));
	while (*argv)
	{
		if (return_stat(*argv, &sb))
		{
			if (S_ISLNK(sb.st_mode))
			{
				ret[i] = malloc(1000);
				readlink(*argv, ret[i], 1000);
			}
			else
				ret[i] = ft_strdup(*argv);
			++i;
		}
		++argv;
	}
	ret[i] = 0;
	return (ret);
}

int				main(int argc, char **argv)
{
	int		*flags;
	char	**new_args;

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
	if (all_invisible(argv))
		flags[ALL_INVISIBLE] = 1;
	if (argc == 1 || flags[LONG])
		flags[ALONE] = 1;
	new_args = solve_link(argc, argv);
	process(mkl_argv(new_args), flags);
	free(flags);
	ft_free_strsplit(new_args);
	return (0);
}
