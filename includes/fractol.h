/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 10:10:53 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 18:34:32 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include "inputs_osx.h"
# include "libft.h"

# define WIN_WIDTH 1599
# define THREADS_NUMBER 15

# define COLOR_DEPTH 32
# define ENDIAN 1

# define SQUARE(x) x * x
# define CUBE(x) x * x * x
# define POW4(x) x * x * x * x

# define ERR_WRONG_ARGS 0
# define ERR_MLX_INIT 1
# define ERR_MLX_WIN 2
# define ERR_INIT_IMG 3
# define ERR_CACHE 4
# define ERR_HUD 5

# define KEYPRESS_MASK (1L<<0)
# define KEYPRESS 2
# define POINTER_MOTION_MASK (1L<<6)
# define MOTION_NOTIFY 6

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef struct	s_range
{
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
}				t_range;

typedef struct	s_env
{
	void		*init;
	void		*win;
	int			win_h;
	int			thread;
	char		*frac_name;
}				t_env;

typedef struct	s_args
{
	t_env		*env;
	int			*cache;
	int			mode;
	t_vec2		j_param;
	int			iter_max;
	int			color;
	double		zoom;
	double		z_min;
	t_range		range;
	int			mouse;
}				t_args;

typedef struct	s_img
{
	void		*ptr;
	int			color_depth;
	int			width;
	int			height;
	int			endian;
	char		*data;
}				t_img;

typedef struct	s_thread
{
	t_args		*args;
	t_img		*img;
	int			(*(*f))(t_vec2, t_args*);
	t_vec2		start;
	t_vec2		end;
	t_vec2		inc;
}				t_thread;

/*
** image drawing functions
*/

int				init_img(t_img *img, t_args *args);
int				win_draw(void *args);
int				draw_fractal(t_args *args, int recalc);
void			transparent_font(t_img *img);
int				hud_draw(t_args *args);
void			put_pixel(t_img *img, t_vec2 pos, int color);
void			*draw_img_threads(void *vt_args);
int				manage_th(t_img *img, t_args *args,
								int (*(*f))(t_vec2, t_args*));

/*
** input functions
*/

int				keypress(int keycode, void *args);
int				mouseclick(int button, int x, int y, void *args);
int				mousemove(int x, int y, void *args);

/*
** init functions
*/

void			init_args(t_env *env, t_args *args);
int				choose_mode(char *param);
void			fractal_range(t_args *args);

/*
** color functions
*/

void			choose_color(t_img *img, t_args *args, t_vec2 pos, int i);
int				blend(int bg, int fg);
int				color(float range, float pos);

/*
** error + quit functions
*/

void			error(int error, t_args *args);
int				quit_cross(void *args);
void			quit(t_args *args, int state);

/*
** fractal calculation functions
*/

int				mandelbrot(t_vec2 pos, t_args *args);
int				julia(t_vec2 pos, t_args *args);
int				collatz(t_vec2 pos, t_args *args);
int				burningship(t_vec2 pos, t_args *args);
int				birdofprey(t_vec2 pos, t_args *args);
int				juliabird(t_vec2 pos, t_args *args);
int				burningjulia(t_vec2 pos, t_args *args);
int				multibrot3(t_vec2 pos, t_args *args);
int				multibrot4(t_vec2 pos, t_args *args);

/*
** number to char* functions
*/

char			*ft_ftoa(double f, double prec);
char			*ft_lltoa(long long n);
char			*ft_e_ftoa(double f, int prec);

#endif
