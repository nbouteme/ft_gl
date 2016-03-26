/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:50:36 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 06:28:51 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/std.h>
#include "mlx.h"
#include "gfx.h"

float		dist(const t_point *a, const t_point *b)
{
	float as;
	float bs;

	as = a->w - b->w;
	bs = a->h - b->h;
	as *= as;
	bs *= bs;
	return (sqrtf(as + bs));
}
