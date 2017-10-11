/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 11:03:32 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 18:21:02 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		choose_color(t_img *img, t_args *args, t_vec2 pos, int i)
{
	if (i == 0)
		put_pixel(img, pos, 0x00000000);
	else
		put_pixel(img, pos, color(64, (float)(i + args->color)));
}

static void	draw_img(t_img *img, t_args *args, int (*(*f))(t_vec2, t_args*))
{
	t_vec2	pos;
	t_vec2	c;
	t_vec2	inc;
	int		i;

	pos.y = 0;
	c.y = args->range.y_min;
	inc.x = (args->range.x_max - args->range.x_min) / img->width;
	inc.y = (args->range.y_max - args->range.y_min) / img->height;
	while (pos.y < img->height)
	{
		pos.x = 0;
		c.x = args->range.x_min;
		while (pos.x < img->width)
		{
			i = f[args->mode](c, args);
			choose_color(img, args, pos, i);
			args->cache[(int)pos.y * img->width + (int)pos.x] = i;
			c.x += inc.x;
			pos.x++;
		}
		c.y += inc.y;
		pos.y++;
	}
}

static void	init_fractals_table(int (*(*f))(t_vec2, t_args*))
{
	f[0] = &(julia);
	f[1] = &(mandelbrot);
	f[2] = &(collatz);
	f[3] = &(burningship);
	f[4] = &(birdofprey);
	f[5] = &(burningjulia);
	f[6] = &(juliabird);
	f[7] = &(multibrot3);
	f[8] = &(multibrot4);
}

static void	actualize_img(t_args *args, t_img *img)
{
	t_vec2	pos;
	int		i;
	t_env	*env;

	env = args->env;
	pos.y = 0;
	while (pos.y < img->height)
	{
		pos.x = 0;
		while (pos.x < img->width)
		{
			i = args->cache[(int)pos.y * img->width + (int)pos.x];
			if (i == 0)
				put_pixel(img, pos, 0x00000000);
			else
				put_pixel(img, pos, color(64, (float)(i + args->color)));
			pos.x++;
		}
		pos.y++;
	}
}

int			draw_fractal(t_args *args, int recalc)
{
	t_img	img;
	int		(*f[9])(t_vec2, t_args*);

	init_fractals_table(&f[0]);
	if (!init_img(&img, args))
		return (ERR_INIT_IMG);
	if (args->cache && !recalc)
		actualize_img(args, &img);
	else
	{
		if (!args->cache)
			if (!(args->cache =
					(int*)ft_memalloc(sizeof(int) * img.width * img.height)))
				return (ERR_CACHE);
		if (!args->env->thread || !manage_th(&img, args, &f[0]))
			draw_img(&img, args, &f[0]);
	}
	transparent_font(&img);
	mlx_clear_window(((t_args*)args)->env->init, ((t_args*)args->env->win));
	mlx_put_image_to_window(((t_args*)args)->env->init,
		((t_args*)args)->env->win, img.ptr, 0, 0);
	if (!(hud_draw((t_args*)args)))
		return (ERR_HUD);
	mlx_destroy_image(((t_args*)args)->env->init, img.ptr);
	return (0);
}
