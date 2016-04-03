/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_defs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <nbouteme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 17:52:07 by nbouteme          #+#    #+#             */
/*   Updated: 2016/03/24 02:25:37 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_DEFS_H
# define KEY_DEFS_H

# include "mlx.h"

# ifdef __linux__
#  include <X11/keysym.h>
#  include <X11/Xlib.h>
#  include <X11/Xutil.h>
#  include <X11/extensions/XShm.h>
#  define ESCAPE XK_Escape
#  define LEFT XK_Left
#  define RIGHT XK_Right
#  define UP XK_Up
#  define DOWN XK_Down
#  define KP_ADD XK_KP_Add
#  define KP_SUBTRACT XK_KP_Subtract
#  define KRM KeyReleaseMask
#  define KR KeyRelease
#  define KPM KeyPressMask
#  define KP KeyPress
#  define PMM PointerMotionMask
#  define MN MotionNotify
# else
#  define ESCAPE 53
#  define LEFT 123
#  define RIGHT 124
#  define UP 126
#  define DOWN 125
#  define KP_ADD 69
#  define KP_SUBTRACT 78
#  define KRM 2
#  define KR 3
#  define KPM 1
#  define KP 2
#  define PMM (1 << 6)
#  define MN 6
# endif

typedef struct	s_keybind
{
	char		c;
	int			idx;
}				t_keybind;

const t_keybind	*get_binds();
int				*get_states();
t_point			*get_mousepos();
int				handle_mouse(int button, int x, int y, t_display *d);

#endif
