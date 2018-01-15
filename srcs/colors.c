/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:29:18 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/15 17:29:09 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			get_color(int mode)
{
	if (S_ISREG(mode))
		return (37);
	else if (S_ISDIR(mode))
		return (34);
	else if (S_ISBLK(mode))
		return (34);
	else if (S_ISCHR(mode))
		return (35);
	else if (S_ISFIFO(mode))
		return (36);
	else if (S_ISLNK(mode))
		return (35);
	else if (S_ISSOCK(mode))
		return (32);
	return (37);
}
