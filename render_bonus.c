/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 02:07:31 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/16 06:29:16 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void	trait_julia(t_complex *z, t_complex *c, t_complex pixel,
		t_fractol *fractol)
{
	z->r = pixel.r;
	z->i = pixel.i;
	c->r = fractol->julia.r;
	c->i = fractol->julia.i;
}

void	trait_burning_ship(t_complex *z)
{
	z->r = fabs(z->r);
	z->i = fabs(z->i);
}

int	get_pixel_color(t_fractol *fractol, t_complex pixel, char *name)
{
	t_complex	tmp;
	t_complex	z;
	t_complex	c;
	int			i;

	z.r = 0;
	z.i = 0;
	c.r = pixel.r;
	c.i = pixel.i;
	if (name[0] == 'j')
		trait_julia(&z, &c, pixel, fractol);
	i = -1;
	while (++i < fractol->max_iter && z.r * z.r + z.i * z.i < 4)
	{
		if (name[0] == 'b')
			trait_burning_ship(&z);
		tmp.r = z.r * z.r - z.i * z.i;
		z.i = 2 * z.r * z.i + c.i;
		z.r = tmp.r + c.r;
	}
	if (i == fractol->max_iter)
		return (0x00);
	return (ft_scale(i, 0x00, 0xFFFFFFFF, fractol->max_iter));
}

void	render_fractol(t_fractol *fractol)
{
	int			x;
	int			y;
	t_complex	pixel;
	int			i;

	i = 0;
	mlx_clear_window(fractol->mlx, fractol->mlx_win);
	while (i < WIDTH * HEIGHT)
	{
		x = i / HEIGHT;
		y = i % HEIGHT;
		pixel.r = ft_scale(x, fractol->x_min, fractol->x_min + 4, WIDTH
				* fractol->zoom) + fractol->shift_x;
		pixel.i = ft_scale(y, fractol->y_min, fractol->y_min + 4, HEIGHT
				* fractol->zoom) + fractol->shift_y;
		my_mlx_pixel_put(&fractol->mlx_img, x, y, get_pixel_color(fractol,
				pixel, fractol->name));
		i++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->mlx_win,
		fractol->mlx_img.ptr, 0, 0);
}
