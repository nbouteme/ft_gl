#include "gfx.h"

inline static t_v8i from_scalar(int n)
{
	return (t_v8i){n, n, n, n, n, n, n, n };
}

t_v8i edge_init(const t_bpoint *v0, const t_bpoint *v1, const t_bpoint *p, t_edge *ret)
{
	t_v8i x_y[2];
	int a;
	int b;
	int c;

	a = v0->h - v1->h;
	b = v1->w - v0->w;
	c = v0->w * v1->h - v0->h * v1->w;
	ret->stepx = from_scalar(a << 3);
	ret->stepy = from_scalar(b);
	x_y[0] = from_scalar(p->w) + ((t_v8i){0, 1, 2, 3, 4, 5, 6, 7});
	x_y[1] = from_scalar(p->h);	
	return from_scalar(a) * x_y[0] + ret->stepy * x_y[1] + from_scalar(c);
}
