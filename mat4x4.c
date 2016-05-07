#include "ft_math.h"
#include <string.h>
#include <math.h>
#include <libft/std.h>

const t_mat4x4 *mulm4m4(const t_mat4x4 a, const t_mat4x4 b)
{
	static __thread t_mat4x4 ret;
	unsigned i;
	unsigned j;
	unsigned k;

	memset(ret, 0, sizeof(ret));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				ret[i][j] += b[i][k] * a[k][j];
				++k;
			}
			++j;
		}
		++i;
	}
	return (&ret);
}

const t_vec4 *mulm4v4(const t_mat4x4 a, const t_vec4 b)
{
	static __thread t_vec4 ret;
	unsigned i;
	unsigned j;

	memset(ret, 0, sizeof(ret));
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret[i] += a[j][i] * b[j];
			++j;
		}
		++i;
	}
	return (&ret);
}

const t_mat4x4 *idm4()
{
	static __thread t_mat4x4 ret =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
	return (&ret);
}

const t_mat4x4 *perspective(float fov, float ar, float near, float far)
{
	float dist;
	float tanf2;
	static __thread t_mat4x4 ret;

	dist = far - near;
	tanf2 = tanf(fov * 0.5f);
	ft_memcpy(ret, (t_mat4x4)
		{
			{ 1.0f / (ar * tanf2), 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f / tanf2, 0.0f, 0.0f },
			{ 0.0f, 0.0f, -(near + far) / dist, -1.0f },
			{ 0.0f, 0.0f, -(2 * near * far) / dist, 0.0f }
		}, sizeof(ret));
	return (&ret);
}

float dotv3(const t_vec3 a, const t_vec3 b)
{
	float ret;
	unsigned i;

	ret = 0;
	i = 0;
	while (i < 3)
	{
		ret += a[i] * b[i];
		++i;
	}
	return (ret);
}



const t_vec3 *subv3(const t_vec3 a, const t_vec3 b)
{
	static __thread t_vec3 ret;

	unsigned i;

	i = 0;
	while (i < 3)
	{
		ret[i] = a[i] - b[i];
		++i;
	}
	return (&ret);
}

const t_vec3 *crossv3(const t_vec3 a, const t_vec3 b)
{
	static __thread t_vec3 ret;

	ret[0] = a[1] * b[2] - a[2] * b[1];
	ret[1] = a[2] * b[0] - a[0] * b[2];
	ret[2] = a[0] * b[1] - a[1] * b[0];
	return (&ret);
}

float	normev3(const t_vec3 rhs)
{
	return (sqrtf((rhs[0] * rhs[0]) +
				  (rhs[1] * rhs[1]) +
				  (rhs[2] * rhs[2])));
}

const t_vec3	*normalizev3(const t_vec3 a)
{
	static __thread t_vec3 ret;
	float	norme;

	norme = 1.0f / normev3(a);
	ret[0] = a[0] * norme;
	ret[1] = a[1] * norme;
	ret[2] = a[2] * norme;
	return (&ret);
}

const t_mat4x4 *lookat(const t_vec3 eye, const t_vec3 target, const t_vec3 up)
{
	static __thread t_mat4x4 ret;
	t_vec3 f;
	t_vec3 s;
	t_vec3 u;

	ft_memcpy(f, normalizev3(*subv3(target, eye)), sizeof(f));
	ft_memcpy(s, normalizev3(*crossv3(f, up)), sizeof(s));
	ft_memcpy(u, crossv3(s, f), sizeof(u));
	ft_memcpy(ret, (t_mat4x4)
		   {
			   {s[0], u[0], -f[0], 0.0f},
			   {s[1], u[1], -f[1], 0.0f},
			   {s[2], u[2], -f[2], 0.0f},
			   {-dotv3(s, eye), -dotv3(u, eye), dotv3(f, eye), 1.0f}
		   }, sizeof(ret));
	return (&ret);
}
/*
int main()
{
	t_mat4x4 a, b, c;
	t_vec4 d;
	ft_memcpy(a, lookat((t_vec3){0.1f, 0.1f, 1.0f},
					 (t_vec3){0.0f, 0.0f, 0.0f},
					 (t_vec3){0.0f, 0.0f, 1.0f}), sizeof(a));
	ft_memcpy(b, perspective(M_PI / 4.0f, 1.0f, 1.0f, 1000.0f), sizeof(b));
	ft_memcpy(c, mulm4m4(a, b), sizeof(c));
	ft_memcpy(d, mulm4v4(c, (t_vec4){0.0f, 0.75f, 0.0f, 1.0f}), sizeof(d));

    return 0;
}
*/
