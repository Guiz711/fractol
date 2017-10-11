/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 12:25:25 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 18:35:03 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		quit(t_args *args, int state)
{
	if (args->cache)
		free(args->cache);
	if (args->env->frac_name)
		free(args->env->frac_name);
	if (args->env->win && args->env->init)
		mlx_destroy_window((void*)args->env->init, (void*)args->env->win);
	exit(state);
}

int			quit_cross(void *args)
{
	quit((t_args*)args, EXIT_SUCCESS);
	return (1);
}

void		error(int error, t_args *args)
{
	if (error == ERR_WRONG_ARGS)
	{
		ft_putendl_fd("Error: Wrong number of args or invalid arg", 2);
		ft_putstr_fd("Usage: 1 argument, possible values: mandelbrot, ", 2);
		ft_putstr_fd("julia, collatz, burningship, birdofprey, ", 2);
		ft_putendl_fd("burningjulia, juliabird, multibrot3, multibrot4", 2);
	}
	if (error == ERR_MLX_INIT)
		ft_putendl_fd("Error: mlx couldn't be initialized", 2);
	if (error == ERR_MLX_WIN)
		ft_putendl_fd("Error: mlx window couldn't be initialized", 2);
	if (error == ERR_INIT_IMG)
		ft_putendl_fd("Error: image couldn't be initialized", 2);
	if (error == ERR_CACHE)
		ft_putendl_fd("Error: cache couldn't be allocated", 2);
	if (error == ERR_HUD)
		ft_putendl_fd("Error: HUD couldn't be drawn", 2);
	quit(args, EXIT_FAILURE);
}
