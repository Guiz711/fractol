/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_calc_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 12:49:17 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 16:34:05 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mandelbrot(t_vec2 pos, t_args *args)
{
	int		i;
	t_vec2	z;
	t_vec2	z_new;

	z_new.x = args->j_param.x;
	z_new.y = args->j_param.y;
	if (SQUARE(z_new.x) + SQUARE(z_new.y) > 4)
		return (1);
	i = 0;
	while (SQUARE(z_new.x) + SQUARE(z_new.y) <= 4 && i < args->iter_max)
	{
		z.x = z_new.x;
		z.y = z_new.y;
		z_new.x = SQUARE(z.x) - SQUARE(z.y) + pos.x;
		z_new.y = 2 * z.x * z.y + pos.y;
		if (z_new.x == z.x && z_new.y == z.y)
			return (0);
		i++;
	}
	if (i == args->iter_max)
		return (0);
	else
		return (i);
}

int		multibrot3(t_vec2 pos, t_args *args)
{
	int		i;
	t_vec2	z;
	t_vec2	z_new;

	z_new.x = args->j_param.x;
	z_new.y = args->j_param.y;
	if (SQUARE(z_new.x) + SQUARE(z_new.y) > 4)
		return (1);
	i = 0;
	while (SQUARE(z_new.x) + SQUARE(z_new.y) <= 4 && i < args->iter_max)
	{
		z.x = z_new.x;
		z.y = z_new.y;
		z_new.x = CUBE(z.x) - 3 * z.x * SQUARE(z.y) + pos.x;
		z_new.y = 3 * SQUARE(z.x) * z.y - CUBE(z.y) + pos.y;
		i++;
	}
	if (i == args->iter_max)
		return (0);
	else
		return (i);
}

int		multibrot4(t_vec2 pos, t_args *args)
{
	int		i;
	t_vec2	z;
	t_vec2	z_new;

	z_new.x = args->j_param.x;
	z_new.y = args->j_param.y;
	if (SQUARE(z_new.x) + SQUARE(z_new.y) > 4)
		return (1);
	i = 0;
	while (SQUARE(z_new.x) + SQUARE(z_new.y) <= 4 && i < args->iter_max)
	{
		z.x = z_new.x;
		z.y = z_new.y;
		z_new.x = POW4(z.x) + POW4(z.y) - 6 * SQUARE(z.x) * SQUARE(z.y) + pos.x;
		z_new.y = 4 * CUBE(z.x) * z.y - 4 * z.x * CUBE(z.y) + pos.y;
		i++;
	}
	if (i == args->iter_max)
		return (0);
	else
		return (i);
}

int		julia(t_vec2 pos, t_args *args)
{
	int		i;
	t_vec2	z;
	t_vec2	z_new;

	if (SQUARE(pos.x) + SQUARE(pos.y) > 4)
		return (1);
	z_new.x = pos.x;
	z_new.y = pos.y;
	i = 0;
	while (SQUARE(z_new.x) + SQUARE(z_new.y) <= 4 && i < args->iter_max)
	{
		z.x = z_new.x;
		z.y = z_new.y;
		z_new.x = SQUARE(z.x) - SQUARE(z.y) + args->j_param.x;
		z_new.y = 2 * z.x * z.y + args->j_param.y;
		i++;
	}
	if (i == args->iter_max)
		return (0);
	else
		return (i);
}

int		collatz(t_vec2 pos, t_args *args)
{
	int		i;
	double	c;
	double	s;
	t_vec2	z;
	t_vec2	z_new;

	if (SQUARE(pos.x) + SQUARE(pos.y) > 20)
		return (1);
	z_new.x = pos.x;
	z_new.y = pos.y;
	i = 0;
	while (SQUARE(z_new.x) + SQUARE(z_new.y) <= 20 && i < args->iter_max)
	{
		z.x = z_new.x;
		z.y = z_new.y;
		c = cos(M_PI * z.x) * cosh(M_PI * z.y);
		s = sin(M_PI * z.x) * sinh(M_PI * z.y);
		z_new.x = args->j_param.x + 0.25
					* (1 + 4 * z.x - c - 2 * z.x * c - 2 * z.y * s);
		z_new.y = args->j_param.y + 0.25
					* (4 * z.y + s + 2 * z.x * s - 2 * z.y * c);
		i++;
	}
	return ((i == args->iter_max) ? 0 : i);
}
