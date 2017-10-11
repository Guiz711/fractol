/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_calc_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 13:13:39 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/10 18:36:31 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		burningship(t_vec2 pos, t_args *args)
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
		z_new.y = 2 * fabs(z.x * z.y) + pos.y;
		i++;
	}
	if (i == args->iter_max)
		return (0);
	else
		return (i);
}

int		burningjulia(t_vec2 pos, t_args *args)
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
		z_new.y = 2 * fabs(z.x * z.y) + args->j_param.y - 0.6;
		i++;
	}
	if (i == args->iter_max)
		return (0);
	else
		return (i);
}

int		birdofprey(t_vec2 pos, t_args *args)
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
		z_new.x = (3 * SQUARE(z.x) - SQUARE(z.y)) * fabs(z.y) + pos.x;
		z_new.y = (SQUARE(z.x) - 3 * SQUARE(z.y)) * fabs(z.x) + pos.y;
		i++;
	}
	if (i == args->iter_max)
		return (0);
	else
		return (i);
}

int		juliabird(t_vec2 pos, t_args *args)
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
		z_new.x = (3 * SQUARE(z.x) - SQUARE(z.y)) * fabs(z.y) + args->j_param.x;
		z_new.y = (SQUARE(z.x) - 3 * SQUARE(z.y)) * fabs(z.x) + args->j_param.y;
		i++;
	}
	if (i == args->iter_max)
		return (0);
	else
		return (i);
}
