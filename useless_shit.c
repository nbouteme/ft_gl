/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useless_shit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:51:15 by nbouteme          #+#    #+#             */
/*   Updated: 2016/04/01 15:39:51 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/std.h>
#include "mlx.h"
#include "gfx.h"
#include <stdio.h>

void	present(t_graphics *g)
{
	int i;
	int j;
	int max;

	max = g->dim.w * g->dim.h;
	i = 0;
	j = 0;
	while (i < max)
	{
		g->fb[i] = (int)(g->draw_surface[j] * 255) << 16
			| (int)(g->draw_surface[j + 1] * 255) << 8
			| (int)(g->draw_surface[j + 2] * 255);
		g->fb[i] &= 0xFFFFFF;
		++i;
		j += 3;
	}
	mlx_put_image_to_window(g->d->conn, g->d->win, g->int_img, 0, 0);
}

void	clear_graphics(t_graphics *g)
{
	int max;
	max = g->dim.w * g->dim.h;
	ft_memset(g->draw_surface, 0, max * 12);
}
