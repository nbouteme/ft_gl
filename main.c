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

void	*readraw(int fd)
{
	void	*buf;
	void	*tmp;
	void	*ret;
	t_u64	n;
	t_u64	total;

	total = 0;
	buf = ft_memalloc(64);
	ret = 0;
	tmp = ret;
	while ((n = read(fd, buf, 64)) > 0)
	{
		ft_bzero(buf + n, 64 - n);
		ret = realloc(ret, total + n);
		tmp = ret + total;
		ft_memcpy(tmp, buf, n);
		total += n;
	}
	free(buf);
	return (ret);
}

#include "gfx.h"
#include <fcntl.h>

int		main()
{
	//g_cube = readraw(open("/home/mirai/kek", O_RDONLY));
	run_display(new_display());
}
