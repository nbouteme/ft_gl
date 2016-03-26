/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:47:34 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 01:33:24 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gfx.h"
#include "clip.h"

static int	gen_rel(const t_point *a)
{
	int ret;

	ret = 0;
	ret = a->w < 0 ? ret | LEFT : ret;
	ret = a->h < 0 ? ret | BOT : ret;
	ret = a->w > 420 ? ret | RIGHT : ret;
	ret = a->h > 420 ? ret | TOP : ret;
	return (ret);
}

void		apply_clip(t_clip t, int rtmp)
{
	if (rtmp & TOP)
	{
		t.out->w = t.a[0] + (t.b[0] - t.a[0]) * (420.0f - t.a[1]) /
			(t.b[1] - t.a[1]);
		t.out->h = 420.0f;
	}
	else if (rtmp & BOT)
	{
		t.out->w = t.a[0] + (t.b[0] - t.a[0]) * -t.a[1] / (t.b[1] - t.a[1]);
		t.out->h = 0;
	}
	else if (rtmp & RIGHT)
	{
		t.out->w = 420.0f;
		t.out->h = t.a[1] + (t.b[1] - t.a[1]) * (420.0f - t.a[0]) /
			(t.b[0] - t.a[0]);
	}
	else if (rtmp & LEFT)
	{
		t.out->w = 0.0f;
		t.out->h = t.a[1] + (t.b[1] - t.a[1]) * -t.a[0] / (t.b[0] - t.a[0]);
	}
}

int			clip(t_graphics *g, t_point *a, t_point *b)
{
	int		ra;
	int		rb;
	int		rtmp;
	int		ret;
	float	*vals[2];

	(void)g;
	vals[0] = (float[]){a->w, a->h};
	vals[1] = (float[]){b->w, b->h};
	ra = gen_rel(a);
	rb = gen_rel(b);
	while (1)
	{
		if ((ret = !(ra | rb)) || (ra & rb))
			return (ret);
		rtmp = ra ? ra : rb;
		apply_clip((t_clip){ra ? a : b, vals[0], vals[1]}, rtmp);
		if (rtmp == ra)
			ra = gen_rel(a);
		else
			rb = gen_rel(b);
	}
	return (0);
}
