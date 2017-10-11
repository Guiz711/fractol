/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 11:04:04 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 17:19:48 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	hud_draw3(t_args *args)
{
	char	*s;

	if (args->env->thread)
	{
		if (!(s = ft_strdup("ON")))
			return (0);
	}
	else if (!(s = ft_strdup("OFF")))
		return (0);
	mlx_string_put(args->env->init, args->env->win, 10, 240, 0x00FFFFFF,
		"Threading :");
	mlx_string_put(args->env->init, args->env->win, 125, 240, 0x00FFFFFF, s);
	ft_memdel((void**)&s);
	return (1);
}

static int	hud_draw2(t_args *args)
{
	char	*s;

	if (!(s = ft_ftoa(args->j_param.y, 3)))
		return (0);
	mlx_string_put(args->env->init, args->env->win, 165, 140, 0x00FFFFFF, s);
	ft_memdel((void**)&s);
	mlx_string_put(args->env->init, args->env->win, 10, 180, 0x00FFFFFF,
		"Center x :");
	if (!(s = ft_ftoa(args->range.x_min +
			(args->range.x_max - args->range.x_min) / 2, 7)))
		return (0);
	mlx_string_put(args->env->init, args->env->win, 115, 180, 0x00FFFFFF, s);
	ft_memdel((void**)&s);
	mlx_string_put(args->env->init, args->env->win, 10, 200, 0x00FFFFFF,
		"Center y :");
	if (!(s = ft_ftoa(args->range.y_min +
			(args->range.y_max - args->range.y_min) / 2, 7)))
		return (0);
	mlx_string_put(args->env->init, args->env->win, 115, 200, 0x00FFFFFF, s);
	ft_memdel((void**)&s);
	return (hud_draw3(args));
}

int			hud_draw(t_args *args)
{
	char	*s;

	if (!(s = ft_e_ftoa(args->zoom, 2)))
		return (0);
	mlx_string_put(args->env->init, args->env->win, 10, 20, 0x00FFFFFF,
		args->env->frac_name);
	mlx_string_put(args->env->init, args->env->win, 10, 60, 0x00FFFFFF,
		"Zoom Level :");
	mlx_string_put(args->env->init, args->env->win, 135, 60, 0x00FFFFFF, s);
	ft_memdel((void**)&s);
	mlx_string_put(args->env->init, args->env->win, 10, 80, 0x00FFFFFF,
		"Iterations :");
	if (!(s = ft_itoa((int)args->iter_max)))
		return (0);
	mlx_string_put(args->env->init, args->env->win, 135, 80, 0x00FFFFFF, s);
	ft_memdel((void**)&s);
	mlx_string_put(args->env->init, args->env->win, 10, 120, 0x00FFFFFF,
		"Mouse Param x :");
	if (!(s = ft_ftoa(args->j_param.x, 3)))
		return (0);
	mlx_string_put(args->env->init, args->env->win, 165, 120, 0x00FFFFFF, s);
	ft_memdel((void**)&s);
	mlx_string_put(args->env->init, args->env->win, 10, 140, 0x00FFFFFF,
		"Mouse Param y :");
	return (hud_draw2(args));
}

int			win_draw(void *args)
{
	t_env	*env;
	int		err;

	env = ((t_args*)args)->env;
	if ((err = draw_fractal((t_args*)args, 1)))
		error(err, (t_args*)args);
	return (1);
}
