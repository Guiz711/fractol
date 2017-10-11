/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 10:29:27 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/10 18:31:31 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	color2(int x, unsigned char *rgb)
{
	if (x >= 512 && x < 768)
	{
		rgb[2] = 0;
		rgb[1] = 255;
		rgb[0] = x - 512;
	}
	else if (x >= 768 && x < 1024)
	{
		rgb[2] = 0;
		rgb[1] = 1023 - x;
		rgb[0] = 255;
	}
	else if (x >= 1024 && x < 1280)
	{
		rgb[2] = x - 1024;
		rgb[1] = 0;
		rgb[0] = 255;
	}
	else if (x >= 1280 && x < 1536)
	{
		rgb[2] = 255;
		rgb[1] = 0;
		rgb[0] = 1535 - x;
	}
}

int			color(float range, float pos)
{
	int				x;
	unsigned char	rgb[4];
	int				*color;

	x = pos * (1536 / range);
	rgb[3] = 0x22;
	if (x >= 1536)
		x = x % 1536;
	if (x >= 0 && x < 256)
	{
		rgb[2] = 255;
		rgb[1] = x;
		rgb[0] = 0;
	}
	else if (x >= 256 && x < 512)
	{
		rgb[2] = 511 - x;
		rgb[1] = 255;
		rgb[0] = 0;
	}
	else
		color2(x, &rgb[0]);
	color = (int*)rgb;
	return (*color);
}

static void	normalize_color(float *n_col, int color)
{
	unsigned char	*c;

	c = (unsigned char*)&color;
	n_col[0] = (float)c[0] / 255;
	n_col[1] = (float)c[1] / 255;
	n_col[2] = (float)c[2] / 255;
	n_col[3] = (float)c[3] / 255;
}

int			blend(int bg, int fg)
{
	float			new[4];
	float			n_bg[4];
	float			n_fg[4];
	unsigned char	final[4];

	normalize_color(&n_bg[0], bg);
	normalize_color(&n_fg[0], fg);
	new[3] = 1 - (1 - n_fg[3]) * (1 - n_bg[3]);
	if (new[3] < 0.000001)
		return (0);
	new[2] = n_fg[2] * n_fg[3] / new[3] + n_bg[2] * n_bg[3]
		* (1 - n_fg[3]) / new[3];
	new[1] = n_fg[1] * n_fg[3] / new[3] + n_bg[1] * n_bg[3]
		* (1 - n_fg[3]) / new[3];
	new[0] = n_fg[0] * n_fg[3] / new[3] + n_bg[0] * n_bg[3]
		* (1 - n_fg[3]) / new[3];
	final[0] = (char)(new[0] * 255);
	final[1] = (char)(new[1] * 255);
	final[2] = (char)(new[2] * 255);
	final[3] = 0x00;
	return ((int)*((int*)final));
}
