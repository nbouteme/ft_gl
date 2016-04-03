/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_detect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 02:04:04 by nbouteme          #+#    #+#             */
/*   Updated: 2016/03/24 01:31:30 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "key_defs.h"

extern int g_key_states[0x10000];
extern t_point g_mouse_pos;
extern const t_keybind g_binds[];

#ifndef __linux__

static int	key_idx(int k)
{
	int i;

	i = 0;
	while (i < 47)
		if (get_binds()[i].c == k)
			return (get_binds()[i].idx);
		else
			++i;
	return (-1);
}

int			is_key_pressed(int key)
{
	int i;

	if (ft_isalpha(key) && (i = key_idx(key)) != -1)
		return (get_states()[i]);
	return (get_states()[key]);
}

#else

int			is_key_pressed(int key)
{
	return (get_states()[key]);
}

#endif
