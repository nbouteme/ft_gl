/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:36:55 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 05:26:39 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H

# include <libft/std.h>
# include "math.h"

# define SIGN(x) ((x > 0) ? 1 : ((x < 0)? -1 : 0))
# define ABS(x) ((x < 0) ? -(x) : (x))

typedef struct s_display	t_display;

typedef struct				s_point
{
	int						w;
	int						h;
	float					z;
}							t_point;

typedef struct				s_bpoint
{
	int						w;
	int						h;
}							t_bpoint;

typedef struct				s_triangle
{
	t_bpoint					a;
	t_bpoint		 			b;
	t_bpoint		 			c;
}							t_triangle;

typedef struct				s_3triangle
{
	float					a[3];
	float					b[3];
	float					c[3];
}							t_3triangle;

typedef struct				s_drawpara
{
	t_point a;
	t_point b;
	float	dist;
	int		c1;
	int		c2;
}							t_drawpara;

typedef struct	s_vertex_input
{
	t_u64	id;
	void	*uniform;
	void	*attribute;
}				t_vertex_input;

typedef int t_v8i __attribute__((vector_size(32)));

typedef struct	s_edge
{
    t_v8i stepx;
    t_v8i stepy;
}				t_edge;

t_v8i edge_init(const t_bpoint *v0, const t_bpoint *v1,
				const t_bpoint *origin, t_edge *ret);

typedef struct	s_fragment_input
{
	const void		*uniform;
	const t_bpoint	*coords;
}				t_fragment_input;

typedef struct	s_vertex_output
{
	float		position[4];
}				t_vertex_output;

typedef void(*t_vertex_shader)(const t_vertex_input *vertex_in,
							   float position[4], void *varying);
typedef void(*t_fragment_shader)(const t_fragment_input *vertex_in,
								 float fragment[3], void *varying);

typedef struct	s_shader
{
	void				*uniforms;
	t_vertex_shader 	vertex;
	t_fragment_shader	fragment;
}				t_shader;

typedef struct				s_graphics
{
	void					*int_img;
	float					*z;
	int						*fb;
	float					*draw_surface;
	t_display				*d;
	void					*buffer_data;
	t_u64					n_elem;
	t_u64					s_elem;
	t_u64					varying_s;
	t_shader				*shader;
	t_point					dim;
	unsigned				color;
	float					*var;
}							t_graphics;

typedef struct				s_sparse_model
{
	t_dlisthead				*verts;
	int						w;
	int						h;
}							t_sparse_model;

typedef struct				s_vertex
{
	int						x;
	int						y;
	int						z;
	unsigned				color;
}							t_vertex;

void						draw_point_bare(t_graphics *g, t_point pos);
void						draw_point(t_graphics *g, t_point pos);
int							clip(t_graphics *g, t_point *a, t_point *b);
t_graphics					*new_graphics(t_display *d);
unsigned					get_pixel(t_graphics *g, t_point pos);
int							is_outside(t_graphics *g, t_point a);
void						present(t_graphics *g);
void						clear_graphics(t_graphics *g);
void						draw_line(t_graphics *g, t_point a, t_point b);
int							disp_expose(t_display *d);
void						draw_line_bare(t_graphics *g, t_point a, t_point b);
t_drawpara					*draw_para_ctl();
void						draw_tris(t_graphics *g, t_u64 n);


typedef struct	s_vert_attr
{
	float		xy[3];
	float		color[3];	
}				t_vert_attr;

extern t_vert_attr *g_cube;

#endif
