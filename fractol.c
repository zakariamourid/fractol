/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 02:08:27 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/16 16:42:27 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_fractol	*get_fractol(void)
{
	static t_fractol	fractol;

	return (&fractol);
}

static t_fractol	*fractol_init(void)
{
	t_fractol	*fractol;

	fractol = get_fractol();
	fractol->max_iter = MAX_ITERATIONS;
	fractol->zoom = 1;
	fractol->x_min = -2;
	fractol->y_min = -2;
	fractol->julia.r = -.835;
	fractol->julia.i = -.321;
	return (fractol);
}

static int	mouse_hook(int keycode)
{
	t_fractol	*fractol;

	fractol = get_fractol();
	if (keycode == 5)
		fractol->zoom *= 1.05;
	else if (keycode == 4)
		fractol->zoom /= 1.05;
	else
		return (0);
	render_fractol(fractol);
	return (0);
}

static int	close_win(void)
{
	close_fract(get_fractol());
	return (0);
}

int	main(int ac, char **av)
{
	t_fractol	*fractol;

	fractol = fractol_init();
	if (!fractol)
		return (0);
	check_args(ac, av, fractol);
	fractol_init2(fractol);
	render_fractol(fractol);
	mlx_key_hook(fractol->mlx_win, key_hook, fractol);
	mlx_mouse_hook(fractol->mlx_win, mouse_hook, NULL);
	mlx_hook(fractol->mlx_win, 17, 0, close_win, NULL);
	mlx_loop(fractol->mlx);
	return (0);
}
