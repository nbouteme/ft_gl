/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:50:11 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 04:27:19 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft/std.h>
#include "mlx.h"
#include "gfx.h"

t_graphics	*new_graphics(t_display *d)
{
	int			osef;
	t_graphics	*g;
	int			i;
	int			max;

	g = malloc(sizeof(t_graphics));
	g->d = d;
	g->int_img = mlx_new_image(d->conn, d->dim.w, d->dim.h);
	g->fb = (int*)mlx_get_data_addr(g->int_img, &osef, &osef, &osef);
	g->dim = d->dim;
	i = 0;
	max = g->dim.w * g->dim.h;
	ft_memset(g->fb, 0, max << 2);
	g->z = malloc(4 * max);
	g->draw_surface = malloc(12 * max);
	while (i < max)
		g->z[i++] = 0x3F800000;
	g->color = 0x00FFFFFF;
	return (g);
}

static int orient2d(const t_bpoint *a, const t_bpoint *b, const t_bpoint *c)
{
    return (b->w - a->w) * (c->h - a->h) - (b->h - a->h) * (c->w - a->w);
}

/*
static int bcenter(const t_triangle *t, const t_bpoint *p, bcenter *w)
{
	w[0] = orient2d(&t->b, &t->c, p);
	w[1] = orient2d(&t->c, &t->a, p);
	w[2] = orient2d(&t->a, &t->b, p);
	return (w[0] >= 0 && w[1] >= 0 && w[2] >= 0) || (w[0] < 0 && w[1] < 0 && w[2] < 0);
}
*/

static int min(int a, int b)
{
	return a < b ? a : b;
}

static int min3(int a, int b, int c)
{
	return min(a, min(b, c));
}

static int max(int a, int b)
{
	return a > b ? a : b;
}

static int max3(int a, int b, int c)
{
	return max(a, max(b, c));
}
/*
static t_triangle *tri_project(const float t[3][4])
{
	static t_triangle ret;

	ret.a.w = (t[0][0] * 0.5f + 0.5f) * 420;
	ret.a.h = (0.5f - t[0][1] * 0.5f) * 420;
	ret.b.w = (t[1][0] * 0.5f + 0.5f) * 420;
	ret.b.h = (0.5f - t[1][1] * 0.5f) * 420;
	ret.c.w = (t[2][0] * 0.5f + 0.5f) * 420;
	ret.c.h = (0.5f - t[2][1] * 0.5f) * 420;
	return &ret;
}
*/
static void tri_project_o(const float t[3][4], t_triangle *ret)
{
	ret->a.w = (t[0][0] * 0.5f + 0.5f) * 420;
	ret->a.h = (0.5f - t[0][1] * 0.5f) * 420;
	ret->b.w = (t[1][0] * 0.5f + 0.5f) * 420;
	ret->b.h = (0.5f - t[1][1] * 0.5f) * 420;
	ret->c.w = (t[2][0] * 0.5f + 0.5f) * 420;
	ret->c.h = (0.5f - t[2][1] * 0.5f) * 420;
}

static inline int bcenter(const t_triangle *t, const t_bpoint *p, float *w, int *val)
{
    float den;

	val[2] = p->w - t->a.w;
	val[5] = p->h - t->a.h;
	den = 1.0f / (val[1] * val[3] - val[0] * val[4]);
    w[1] = (val[2] * val[3] - val[0] * val[5]) * den;
    w[2] = (val[1] * val[5] - val[2] * val[4]) * den;
    w[0] = 1.0f - w[1] - w[2];
	return (w[0] >= 0 && w[1] >= 0 && w[2] >= 0);
}

typedef float	(*t_mat2x2)[2][2];

t_mat2x2 inv_mat2x2(t_mat2x2 a)
{
	static float res[2][2];
	float det = 1.0f / (((*a)[0][0] * (*a)[1][1]) - ((*a)[0][1] * (*a)[1][0]));
	res[0][0] =  (*a)[1][1] * det;
	res[0][1] = -(*a)[0][1] * det;
	res[1][0] = -(*a)[1][0] * det;
	res[1][1] =  (*a)[0][0] * det;
	return &res;
}

typedef struct	s_bary
{
	int hstep[3];
	int vstep[3];
	int bounds[4];
}				t_bary;

t_bary *bake_transform(const t_triangle *t, int *wr)
{
	static t_bary res;
    t_bpoint p;

	p.w = max(min3(t->a.w, t->b.w, t->c.w), 0);
	p.h = max(min3(t->a.h, t->b.h, t->c.h), 0);
    wr[0] = orient2d(&t->b, &t->c, &p);
    wr[1] = orient2d(&t->c, &t->a, &p);
    wr[2] = orient2d(&t->a, &t->b, &p);
	res.hstep[0] = t->a.h - t->b.h;
	res.hstep[1] = t->b.h - t->c.h;
	res.hstep[2] = t->c.h - t->a.h;
	res.vstep[0] = t->b.w - t->a.w;
	res.vstep[1] = t->c.w - t->b.w;
	res.vstep[2] = t->a.w - t->c.w;
    res.bounds[0] = max(min3(t->a.w, t->b.w, t->c.w), 0);
    res.bounds[1] = max(min3(t->a.h, t->b.h, t->c.h), 0);	
    res.bounds[2] = min(max3(t->a.w, t->b.w, t->c.w), 419);
    res.bounds[3] = min(max3(t->a.h, t->b.h, t->c.h), 419);
	return &res;
}
int count;
static inline void render_pix(t_graphics *g, const t_bpoint *p, const t_v8i *w, t_v8i mask)
{
	int i;
	float varinter[g->varying_s / 4];
	unsigned k;

	i = 0;
	while (i < 8)
	{
		if(mask[i] >= 0)
		{
			++count;
			k = ~0;
			/*int triArea = a * pa.x + b * pa.h + c*/
			float t = 1.0f / (22050 * 2);
			while (++k < g->varying_s / 4)
				varinter[k] =  ((float)w[0][i] * t) * g->var[k]
					+ ((float)w[1][i] * t) * g->var[3 + k]
					+ ((float)w[2][i] * t) * g->var[6 + k];
			g->shader->fragment(&(t_fragment_input){g->shader->uniforms, p},
								&g->draw_surface[3 * (420 * p->h + p->w + i)],
								varinter);
		}
		++i;
	}
}

static inline void draw_triangle(t_graphics *g, const float coor[3][4])
{
	t_triangle t;
	t_v8i wr[3];
	t_bpoint p;

	tri_project_o(coor, &t);
	int minx = max(min3(t.a.w, t.b.w, t.c.w), 0),
		miny = max(min3(t.a.h, t.b.h, t.c.h), 0),
		maxx = min(max3(t.a.w, t.b.w, t.c.w), 419),
		maxy = min(max3(t.a.h, t.b.h, t.c.h), 419);
	p.h = miny;
	p.w = minx;
	count = 0;
	t_edge e01, e12, e20;
	wr[0] = edge_init(&t.b, &t.c, &p, &e12);
	wr[1] = edge_init(&t.c, &t.a, &p, &e20);
	wr[2] = edge_init(&t.a, &t.b, &p, &e01);
	p.h--;
	while (++p.h < maxy)
	{
		t_v8i  w[3] = {wr[0], wr[1], wr[2]};
		p.w = minx - 8;
		while((p.w += 8) < maxx)
		{
			t_v8i mask = w[0] | w[1] | w[2];
			render_pix(g, &p, w, mask);
			w[0] += e12.stepx;
			w[1] += e20.stepx;
			w[2] += e01.stepx;
		}
		wr[0] += e12.stepy;
		wr[1] += e20.stepy;
		wr[2] += e01.stepy;
	}
}

void draw_tris(t_graphics *g, t_u64 n)
{
	t_u64 i;
	t_u64 max;
	float coor[3][4];
	float var[(g->varying_s >> 2) * 3];

	i = 0;
	max = n * 3;
	g->var = &var[0];
	while (i < max)
	{
		g->shader->vertex(&(t_vertex_input){i, g->shader->uniforms,
					(char*)g->buffer_data + (i * g->s_elem)}, coor[0],
			&var[0]);
		g->shader->vertex(&(t_vertex_input){i + 1, g->shader->uniforms,
					(char*)g->buffer_data + ((i + 1) * g->s_elem)}, coor[1],
			&var[g->varying_s >> 2]);
		g->shader->vertex(&(t_vertex_input){i + 2, g->shader->uniforms,
					(char*)g->buffer_data + ((i + 2) * g->s_elem)}, coor[2],
			&var[g->varying_s >> 1]);
		draw_triangle(g, coor);
		i += 3;
	}
}
