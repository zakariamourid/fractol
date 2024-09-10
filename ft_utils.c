/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 02:01:07 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/16 04:26:46 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

double	ft_scale(double num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * (num) / (old_max) + new_min);
}

void	fractol_init2(t_fractol *fractol)
{
	fractol->mlx = mlx_init();
	fractol->mlx_win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "fractol");
	fractol->mlx_img.ptr = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	fractol->mlx_img.addr = mlx_get_data_addr(fractol->mlx_img.ptr,
			&fractol->mlx_img.bpp,
			&fractol->mlx_img.ll,
			&fractol->mlx_img.e);
}
