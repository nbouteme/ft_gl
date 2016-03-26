/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:49:19 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/06 01:32:04 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIP_H
# define CLIP_H

# include "gfx.h"

enum	e_rel
{
	IN = 0x00000000,
	LEFT = 0x00000001,
	RIGHT = 0x00000100,
	TOP = 0x00010000,
	BOT = 0x01000000
};

typedef struct	s_clip
{
	t_point	*out;
	float	*a;
	float	*b;
}				t_clip;

int				clip(t_graphics *g, t_point *a, t_point *b);

#endif
