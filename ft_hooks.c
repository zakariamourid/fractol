/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 02:45:47 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/16 06:09:41 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	reset_all(t_fractol *fractol)
{
	fractol->max_iter = MAX_ITERATIONS;
	fractol->zoom = 1;
	fractol->x_min = -2;
	fractol->y_min = -2;
	fractol->zoom = 1;
	fractol->shift_x = 0;
	fractol->shift_y = 0;
	render_fractol(fractol);
}

static void	handle_move(int keycode, t_fractol *fractol)
{
	if (keycode == 126)
		fractol->shift_y -= 0.5 / fractol->zoom;
	if (keycode == 125)
		fractol->shift_y += 0.5 / fractol->zoom;
	if (keycode == 124)
		fractol->shift_x += 0.5 / fractol->zoom;
	if (keycode == 123)
		fractol->shift_x -= 0.5 / fractol->zoom;
}

int	key_hook(int keycode, t_fractol *fractol)
{
	if ((keycode >= 123 && keycode <= 126) || keycode == 2 || keycode == 0)
	{
		handle_move(keycode, fractol);
		render_fractol(fractol);
	}
	else if (keycode == 15)
		reset_all(fractol);
	else if (keycode == 53)
		close_fract(fractol);
	return (0);
}
