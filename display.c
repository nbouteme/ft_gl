/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 19:17:17 by nbouteme          #+#    #+#             */
/*   Updated: 2016/04/03 12:07:48 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include "mlx.h"
#include "key_defs.h"

void draw_triangle(t_graphics *g, const t_triangle *t);

t_vert_attr *g_cube;

typedef struct
{
	float outcolor[3];
} __attribute__((packed)) t_varying;

#include "ft_math.h"

typedef struct
{
	t_mat4x4 model;
	t_mat4x4 view;
	t_mat4x4 proj;
} t_uni;

t_uni unif;

void identity_shader(const t_vertex_input *in, float pos[4], void *varying)
{
	t_vert_attr *attr;
	const t_uni *tran = in->uniform;
	t_mat4x4 tmp;

	attr = in->attribute;
	ft_memcpy(tmp, *mulm4m4(tran->model, tran->view), sizeof(tmp));
	ft_memcpy(pos, mulm4v4(*mulm4m4(tran->proj, tmp),
						   (float[4]){attr->xyz[0], attr->xyz[1], attr->xyz[2], 1.0f}),
			sizeof(float) << 2);
	pos[2] /= pos[3];
	pos[3] /= pos[3];
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

t_vec3 h = { 0.13f, 0.13f, 1.0f };

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
	memcpy(unif.model, idm4(), sizeof(t_mat4x4));
	memcpy(unif.proj, perspective(M_PI / 4.0f, 1.0f, 1.0f, 1000.0f), sizeof(t_mat4x4));
	memcpy(unif.view, lookat(h,
							 (t_vec3){0.0f, 0.0f, 0.0f},
							 (t_vec3){0.0f, 0.0f, 1.0f}), sizeof(t_mat4x4));
	s.uniforms = &unif;
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
	if (is_key_pressed(ESCAPE))
		exit(42);
	if (is_key_pressed(UP))
		h[1] += 0.5f;
	if (is_key_pressed(DOWN))
		h[1] -= 0.5f;
	if (is_key_pressed(LEFT))
		h[0] += 0.5f;
	if (is_key_pressed(RIGHT))
		h[0] -= 0.5f;
	if (is_key_pressed(KP_ADD))
		h[2] += 0.5f;
	if (is_key_pressed(KP_SUBTRACT))
		h[2] -= 0.5f;

	clear_graphics(d->g);
	redraw(d);
	return (0);
}
