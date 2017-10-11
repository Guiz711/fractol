/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 13:09:37 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 17:17:31 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		init_img(t_img *img, t_args *args)
{
	int		w;
	t_range	r;

	r = args->range;
	img->color_depth = COLOR_DEPTH;
	img->width = WIN_WIDTH;
	img->height = args->env->win_h;
	img->endian = ENDIAN;
	if (!(img->ptr = mlx_new_image(args->env->init, img->width, img->height)))
		return (0);
	w = img->width * (COLOR_DEPTH / 8);
	if (!(img->data = mlx_get_data_addr(img->ptr, &img->color_depth, &w,
		&img->endian)))
		return (0);
	return (1);
}

void	transparent_font(t_img *img)
{
	int i;
	int j;
	int color;
	int width;
	int inc;

	inc = img->color_depth / 8;
	width = img->width * (COLOR_DEPTH / 8);
	i = 0;
	while (i < 270)
	{
		j = 0;
		while (j < 230)
		{
			color = blend((int)*((int*)&img->data[i * width + (j * inc)]),
				0x40000000);
			ft_memcpy(&img->data[i * width + (j * inc)], &color, sizeof(color));
			j++;
		}
		i++;
	}
}

void	put_pixel(t_img *img, t_vec2 pos, int color)
{
	char	*data;
	int		width;
	int		inc;

	data = img->data;
	inc = img->color_depth / 8;
	width = img->width * (COLOR_DEPTH / 8);
	if (pos.x < (width / inc) && pos.y < img->height && pos.x >= 0
		&& pos.y >= 0)
	{
		ft_memcpy(&data[((int)pos.y * width) + ((int)pos.x * inc)], &color,
			sizeof(color));
	}
}
