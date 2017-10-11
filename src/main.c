/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmichaud <gmichaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:23:23 by gmichaud          #+#    #+#             */
/*   Updated: 2017/10/11 18:34:42 by gmichaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char **argv)
{
	t_env	env;
	t_args	args;

	init_args(&env, &args);
	args.env = &env;
	if (argc != 2)
		error(ERR_WRONG_ARGS, &args);
	if ((args.mode = choose_mode(argv[1])) == -1)
		error(ERR_WRONG_ARGS, &args);
	fractal_range(&args);
	if (!(env.init = mlx_init()))
		error(ERR_MLX_INIT, &args);
	if (!(env.win = mlx_new_window(env.init, WIN_WIDTH, env.win_h, "Fractol")))
		error(ERR_MLX_WIN, &args);
	mlx_expose_hook(env.win, &win_draw, &args);
	mlx_hook(env.win, 17, 0L, &quit_cross, &args);
	mlx_hook(env.win, KEYPRESS, KEYPRESS_MASK, &keypress, &args);
	mlx_hook(env.win, MOTION_NOTIFY, POINTER_MOTION_MASK, &mousemove, &args);
	mlx_mouse_hook(env.win, mouseclick, &args);
	mlx_loop(env.init);
	return (0);
}
