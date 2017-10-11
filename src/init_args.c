/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 10:52:56 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 16:38:31 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	fractal_name(t_args *args)
{
	if (args->env->frac_name)
		ft_memdel((void**)&args->env->frac_name);
	if (args->mode == 0)
		args->env->frac_name = ft_strdup("Julia");
	if (args->mode == 1)
		args->env->frac_name = ft_strdup("Mandelbrot");
	if (args->mode == 2)
		args->env->frac_name = ft_strdup("Collatz");
	if (args->mode == 3)
		args->env->frac_name = ft_strdup("Burningship");
	if (args->mode == 4)
		args->env->frac_name = ft_strdup("Birdofprey");
	if (args->mode == 5)
		args->env->frac_name = ft_strdup("Burningjulia");
	if (args->mode == 6)
		args->env->frac_name = ft_strdup("Juliabird");
	if (args->mode == 7)
		args->env->frac_name = ft_strdup("Multibrot POW3");
	if (args->mode == 8)
		args->env->frac_name = ft_strdup("Multibrot POW4");
	return (1);
}

void		fractal_range(t_args *args)
{
	args->range.x_min = -2.7;
	args->range.x_max = 2.27;
	args->range.y_min = -1.4;
	args->range.y_max = 1.4;
	args->zoom = WIN_WIDTH / (args->range.x_max - args->range.x_min);
	args->env->win_h = (args->range.y_max - args->range.y_min) * args->zoom;
	args->z_min = args->zoom;
	fractal_name(args);
}

int			choose_mode(char *param)
{
	if (!ft_strcmp(param, "julia"))
		return (0);
	if (!ft_strcmp(param, "mandelbrot"))
		return (1);
	if (!ft_strcmp(param, "collatz"))
		return (2);
	if (!ft_strcmp(param, "burningship"))
		return (3);
	if (!ft_strcmp(param, "birdofprey"))
		return (4);
	if (!ft_strcmp(param, "burningjulia"))
		return (5);
	if (!ft_strcmp(param, "juliabird"))
		return (6);
	if (!ft_strcmp(param, "multibrot3"))
		return (7);
	if (!ft_strcmp(param, "multibrot4"))
		return (8);
	return (-1);
}

void		init_args(t_env *env, t_args *args)
{
	env->init = NULL;
	env->win = NULL;
	env->frac_name = NULL;
	env->thread = 0;
	args->mode = 0;
	args->iter_max = 100;
	args->color = 0;
	args->j_param.x = 0;
	args->j_param.y = 0;
	args->cache = NULL;
	args->mouse = 1;
}
