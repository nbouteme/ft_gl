/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 16:42:11 by nbouteme          #+#    #+#             */
/*   Updated: 2016/01/27 16:42:13 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <libft/std.h>
#include "mlx.h"

#define B_SIZE (1 << 16)

typedef float	(*t_mat2x2)[2][2];

t_mat2x2 inv_mat2x2(t_mat2x2 a);

float *matmul2(float ti[2][2], float v[2]);

int		main()
{
/*	float a[3][2] =
	{
		{ 210.0f, 105.0f },
		{ 315.0f, 315.0f },
		{ 105.0f, 315.0f }
		};*/
/*	float t[2][2] =
	{
		{ 105.0f, 105.0f - 315.0f },
		{ 210.0f, 315.0f - 315.0f }
	};
	t_mat2x2 r = inv_mat2x2(&t);
	float coefs[3];
	float p[2] = {125, 205};
	float s3[2] = { 105.0f, 315.0f };
	memcpy(coefs, matmul2(*r, (float[2]){p[0] - s3[0], p[1] - s3[1]}), sizeof(float) << 1);
	coefs[2] = 1.0f - coefs[0] - coefs[1];
	return (*r)[0][0];
*/
	run_display(new_display());
}
