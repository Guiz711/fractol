/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:45:40 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 15:41:26 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*draw_img_threads(void *v)
{
	t_thread	*t;
	t_vec2		pos;
	t_vec2		c;
	int			i;

	t = (t_thread*)v;
	pos.y = t->start.y;
	c.y = t->args->range.y_min + t->inc.y * pos.y;
	while (pos.y < t->end.y)
	{
		pos.x = t->start.x;
		c.x = t->args->range.x_min + t->inc.x * pos.x;
		while (pos.x < t->end.x)
		{
			i = t->f[t->args->mode](c, t->args);
			choose_color(t->img, t->args, pos, i);
			t->args->cache[(int)pos.y * t->img->width + (int)pos.x] = i;
			c.x += t->inc.x;
			pos.x++;
		}
		c.y += t->inc.y;
		pos.y++;
	}
	return (NULL);
}

void	init(t_thread *t, t_img *img, int (*(*f))(t_vec2, t_args*), t_args *a)
{
	size_t	i;

	i = 0;
	while (i < THREADS_NUMBER)
	{
		t[i].args = a;
		t[i].img = img;
		t[i].f = f;
		t[i].start.x = 0;
		t[i].end.x = img->width;
		t[i].inc.x = (a->range.x_max - a->range.x_min) / img->width;
		t[i].inc.y = (a->range.y_max - a->range.y_min) / img->height;
		t[i].start.y = (i == 0) ? 0 : img->height / THREADS_NUMBER * i;
		t[i].end.y = (i == THREADS_NUMBER - 1) ? img->height
			: img->height / THREADS_NUMBER * (i + 1);
		i++;
	}
}

int		manage_th(t_img *img, t_args *args, int (*(*f))(t_vec2, t_args*))
{
	pthread_t	t[THREADS_NUMBER];
	t_thread	thread[THREADS_NUMBER];
	int			i;

	i = 0;
	init(&thread[0], img, f, args);
	while (i < THREADS_NUMBER)
	{
		if (pthread_create(&t[i], NULL, &draw_img_threads, &thread[i]))
		{
			while (i--)
				pthread_cancel(t[i]);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < THREADS_NUMBER)
	{
		if (pthread_join(t[i], NULL))
			return (0);
		i++;
	}
	return (1);
}
