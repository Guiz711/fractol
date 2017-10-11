/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 12:07:04 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 17:19:17 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		move_y(int keycode, t_args *args)
{
	int err;

	if (keycode == KEY_S && args->range.y_max < 7)
	{
		args->range.y_min += 50 / args->zoom;
		args->range.y_max += 50 / args->zoom;
		if ((err = draw_fractal(args, 1)))
			error(err, args);
	}
	if (keycode == KEY_W && args->range.y_min > -7)
	{
		args->range.y_min -= 50 / args->zoom;
		args->range.y_max -= 50 / args->zoom;
		if ((err = draw_fractal(args, 1)))
			error(err, args);
	}
}

static void		move_x(int keycode, t_args *args)
{
	int err;

	if (keycode == KEY_A && args->range.x_min > -7)
	{
		args->range.x_min -= 50 / args->zoom;
		args->range.x_max -= 50 / args->zoom;
		if ((err = draw_fractal(args, 1)))
			error(err, args);
	}
	if (keycode == KEY_D && args->range.x_max < 7)
	{
		args->range.x_min += 50 / args->zoom;
		args->range.x_max += 50 / args->zoom;
		if ((err = draw_fractal(args, 1)))
			error(err, args);
	}
}

static void		params_2(int keycode, t_args *args)
{
	int	err;

	if (keycode == KEY_PAD_ADD)
	{
		args->iter_max += 10;
		if ((err = draw_fractal(args, 1)))
			error(err, args);
	}
	if (keycode == KEY_PAD_SUB && args->iter_max > 10)
	{
		args->iter_max -= 10;
		if ((err = draw_fractal(args, 1)))
			error(err, args);
	}
	if (keycode == KEY_R)
	{
		args->mouse = args->mouse ? 0 : 1;
	}
	if (keycode == KEY_T)
	{
		((t_args*)args)->env->thread = ((t_args*)args)->env->thread ? 0 : 1;
		if ((err = draw_fractal(args, 0)))
			error(err, args);
	}
}

static void		params_1(int keycode, t_args *args)
{
	int	err;

	if (keycode == KEY_PAD_9)
	{
		args->color = (args->color == 64) ? 0 : args->color + 1;
		if ((err = draw_fractal(args, 0)))
			error(err, args);
	}
	if (keycode == KEY_PAD_3)
	{
		args->color = (args->color == 0) ? 64 : args->color - 1;
		if ((err = draw_fractal(args, 0)))
			error(err, args);
	}
	if (keycode == KEY_E)
	{
		args->mode = args->mode == 8 ? 0 : args->mode + 1;
		fractal_range(args);
		if ((err = draw_fractal(args, 1)))
			error(err, args);
	}
}

int				keypress(int keycode, void *args)
{
	int	err;

	if (keycode == KEY_ESC)
		quit((t_args*)args, EXIT_SUCCESS);
	if (keycode == KEY_Q)
	{
		((t_args*)args)->j_param.x = 0;
		((t_args*)args)->j_param.y = 0;
		if ((err = draw_fractal(args, 1)))
			error(err, args);
	}
	if (keycode == KEY_Z)
	{
		fractal_range(args);
		if ((err = draw_fractal(args, 1)))
			error(err, args);
	}
	params_1(keycode, (t_args*)args);
	params_2(keycode, (t_args*)args);
	move_x(keycode, (t_args*)args);
	move_y(keycode, (t_args*)args);
	return (1);
}
