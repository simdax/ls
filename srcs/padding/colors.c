/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scornaz <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:29:18 by scornaz           #+#    #+#             */
/*   Updated: 2018/01/18 13:45:50 by scornaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define RED						31
#define GREEN					32
#define ORANGE					33
#define BLUE					34
#define PURPLE					35
#define CYAN					36
#define GREY					37
#define BLACK_BACKGROUND		40
#define RED_BACKGROUND			41
#define GREEN_BACKGROUND		42
#define ORANGE_BACKGROUND		43
#define BLUE_BACKGROUND			44
#define PURPLE_BACKGROUND		45
#define CYAN_BACKGROUND			46
#define GREY_BACKGROUND			47
#define DARK_GREY				90
#define LIGHT_RED				91
#define LIGHT_GREEN				92
#define YELLOW					93
#define LIGHT_BLUE				94
#define LIGHT_PURPLE			95
#define TURQUOISE				96
#define DARK_GREY_BACKGROUND	100
#define LIGHT_RED_BACKGROUND	101
#define LIGHT_GREEN_BACKGROUND	102
#define YELLOW_BACKGROUND		103
#define LIGHT_BLUE_BACKGROUND	104
#define LIGHT_PURPLE_BACKGROUND 105
#define TURQUOISE_BACKGROUND	106

int		get_color(struct stat sb)
{
	int	mode;
	int	exec;

	mode = sb.st_mode;
	exec = ((mode >> 6 & 7) == 7);
	if (S_ISDIR(mode))
		return (CYAN);
	else if (S_ISLNK(mode))
		return (CYAN);
	else if (exec)
		return (RED);
	else if (S_ISREG(mode))
		return (GREY);
	else if (S_ISBLK(mode))
		return (34);
	else if (S_ISCHR(mode))
		return (35);
	else if (S_ISFIFO(mode))
		return (YELLOW);
	else if (S_ISSOCK(mode))
		return (ORANGE);
	return (37);
}
