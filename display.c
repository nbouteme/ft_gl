/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:17:17 by nbouteme          #+#    #+#             */
/*   Updated: 2016/04/01 16:13:55 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "mlx.h"

void draw_triangle(t_graphics *g, const t_triangle *t);

t_vert_attr *g_cube;

typedef struct
{
	float outcolor[3];
} __attribute__((packed)) t_varying;

void identity_shader(const t_vertex_input *in, float pos[4], void *varying)
{
	t_vert_attr *attr;

	attr = in->attribute;
	ft_memcpy(pos, (float[]){attr->xy[0], attr->xy[1], attr->xy[2], 1.0f}, sizeof(float) << 2);
	t_varying *va = varying;
	memcpy(va->outcolor, attr->color, sizeof(float) * 3);
}

void white_shader(const t_fragment_input *in, float frag[3], void *varying)
{
	(void)in;
	(void)varying;
	t_varying *v = varying;
	memcpy(frag, v->outcolor, sizeof(float) * 3);
}

void buffer_va(t_graphics *g, void *data, t_u64 n, t_u64 s)
{
	g->n_elem = n;
	g->s_elem = s;
	g->buffer_data = data;
}

#include <time.h>

void		redraw(t_display *d)
{
	t_vert_attr tri[3];
	t_shader s;

	ft_memcpy(&tri, &(t_vert_attr[3])
			{
				(t_vert_attr){{ 0.0f,  0.75f, 0.0f}, {0.0f, 1.0f, 0.0f}},
				(t_vert_attr){{ 0.75f, -0.75f, 0.0f}, {1.0f, 0.0f, 0.0f}},
				(t_vert_attr){{-0.75f, -0.75f, 0.0f}, {0.0f, 0.0f, 1.0f}},
			}, sizeof(tri));

	static int ret = 0;
	++ret;
	s.uniforms = &ret;
	s.vertex = &identity_shader;
	s.fragment = &white_shader;
	d->g->shader = &s;
	d->g->varying_s = sizeof(t_varying);
	buffer_va(d->g, tri, 3, sizeof(*tri));
	clock_t a = clock(), b;
	draw_tris(d->g, 1);
	b = clock();
	printf("ft: %zu\n", b - a);
}

int			disp_expose(t_display *d)
{
	present(d->g);
	mlx_do_sync(d->conn);
	return (0);
}

int			disp_handle_key(t_display *d)
{
	redraw(d);
	return (0);
}
