#ifndef FT_MATH_H
# define FT_MATH_H

typedef float (t_mat4x4)[4][4] __attribute__ ((aligned (16)));
typedef float (t_mat3x3)[3][3] __attribute__ ((aligned (16)));

typedef float (t_vec4)[4] __attribute__ ((aligned (16)));
typedef float (t_vec3)[3] __attribute__ ((aligned (16)));

const t_mat4x4 *idm4();

const t_mat4x4 *lookat(const t_vec3 eye, const t_vec3 target, const t_vec3 up);

const t_mat4x4 *perspective(float fov, float ar, float near, float far);
const t_mat4x4 *mulm4m4(const t_mat4x4 a, const t_mat4x4 b);
const t_vec4 *mulm4v4(const t_mat4x4 a, const t_vec4 b);

#endif
