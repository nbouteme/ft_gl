/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouteme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 18:41:44 by nbouteme          #+#    #+#             */
/*   Updated: 2016/02/05 01:58:04 by nbouteme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_HANDLE_H
# define KEY_HANDLE_H

int		set_key_handlers(t_display *d);
int		is_key_pressed(int key);
t_point	get_mouse_pos();

#endif
