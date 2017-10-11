/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 11:20:12 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/10 18:41:13 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mousemove(int x, int y, void *args)
{
	t_vec2 c;

	if (!((t_args*)args)->mouse)
		return (1);
	c.x = (float)x / (WIN_WIDTH) * 4 - 2.5;
	c.y = (float)y / ((t_args*)args)->env->win_h * 3 - 1.5;
	if ((float)(((t_args*)args)->j_param.x - c.x) > 0.01
		|| (float)(((t_args*)args)->j_param.x - c.x) < -0.01
		|| (float)(((t_args*)args)->j_param.y - c.y) > 0.01
		|| (float)(((t_args*)args)->j_param.y - c.y) < -0.01)
	{
		((t_args*)args)->j_param.x = c.x;
		((t_args*)args)->j_param.y = c.y;
		draw_fractal((t_args*)args, 1);
	}
	return (1);
}

static void		zoom(int button, int x, int y, void *args)
{
	t_range *range;
	t_vec2	dist;
	t_vec2	conv;
	double	scale;

	range = &((t_args*)args)->range;
	dist.x = range->x_max - range->x_min;
	dist.y = range->y_max - range->y_min;
	scale = (button == 4) ? 1.2 : 0.8;
	conv.x = (range->x_min + ((double)x * (dist.x /
				(dist.x * ((t_args*)args)->zoom))));
	conv.y = (range->y_min + ((double)y * (dist.y /
				(dist.y * ((t_args*)args)->zoom))));
	range->x_min = conv.x - (conv.x - range->x_min) * scale;
	range->x_max = range->x_min + dist.x * scale;
	range->y_min = conv.y - (conv.y - range->y_min) * scale;
	range->y_max = range->y_min + dist.y * scale;
	((t_args*)args)->zoom = (float)WIN_WIDTH / (range->x_max - range->x_min);
}

int				mouseclick(int button, int x, int y, void *args)
{
	static int i = 0;

	if (button == 4 && ((t_args*)args)->zoom > ((t_args*)args)->z_min)
		zoom(button, x, y, args);
	if (button == 5)
	{
		zoom(button, x, y, args);
		i++;
	}
	draw_fractal((t_args*)args, 1);
	return (1);
}
