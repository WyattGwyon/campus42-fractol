/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:09:30 by clouden           #+#    #+#             */
/*   Updated: 2025/09/19 12:10:08 by clouden          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

const t_color_map	*make_color_table(void)
{
	static const t_color_map	color_table[] = {
	{XK_1, 0x00ff00, 0x000000},
	{XK_2, 0x0000ff, 0x000000},
	{XK_3, 0xff0000, 0xfff900},
	{XK_4, 0xff7f00, 0xffffff},
	{XK_5, 0xffff00, 0xff0000},
	{XK_6, 0x556699, 0x009999},
	{XK_7, 0xff0000, 0xff00ff},
	{XK_8, 0x001f3f, 0x0074D9},
	{XK_9, 0x886666, 0x000000},
	{XK_0, 0xffffff, 0x77ff77},
	{XK_d, 0xf00000, 0x00000f},
	{0, 0, 0}
	};

	return (color_table);
}

const t_event_map	*make_event_table(void)
{
	static const t_event_map	event_table[] = { 
	{XK_Up, move_up},
	{XK_Down, move_down},
	{XK_Left, move_left},
	{XK_Right, move_right},
	{XK_l, iter_down},
	{XK_h, iter_up},
	{XK_r, reset},
	{0, NULL}
	};

	return (event_table);
}

const t_wrapper_map	*make_wrapper_table(void)
{
	static const t_wrapper_map	wrapper_table[] = {
	{XK_1, color_wrapper},
	{XK_2, color_wrapper},
	{XK_3, color_wrapper},
	{XK_4, color_wrapper},
	{XK_5, color_wrapper},
	{XK_6, color_wrapper},
	{XK_7, color_wrapper},
	{XK_8, color_wrapper},
	{XK_9, color_wrapper},
	{XK_0, color_wrapper},
	{XK_Up, shift_iterate_wrapper},
	{XK_Down, shift_iterate_wrapper},
	{XK_Left, shift_iterate_wrapper},
	{XK_Right, shift_iterate_wrapper},
	{XK_l, shift_iterate_wrapper},
	{XK_h, shift_iterate_wrapper},
	{XK_r, shift_iterate_wrapper},
	{0, NULL}
	};

	return (wrapper_table);
}
