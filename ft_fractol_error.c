/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 02:02:18 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/16 16:50:44 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	close_fract_v2(void)
{
	ft_putstr("usage :fractol [fractals]\n");
	ft_putstr("fractals:\n");
	ft_putstr("-->Mandelbrot\n");
	ft_putstr("-->Julia [args(optional)] (args default(.835 .321))\n");
	exit(0);
}

int	is_valid(char *data)
{
	int	sign;

	sign = 0;
	if (ft_strlen(data) == 1 && *data == '.')
		return (0);
	if (!data || !*data)
		return (0);
	if (*data == '-' || *data == '+')
		data++;
	while (ft_isdigit(*data))
		data++;
	if (*data == '.' && *data)
		data++;
	while (ft_isdigit(*data))
		data++;
	if (*data == 0)
		return (1);
	return (0);
}

double	ft_atod(char *data)
{
	double	res;
	double	res2;
	int		signe;
	int		i;

	res = 0;
	res2 = 0;
	signe = 1;
	i = 1;
	if (*data == '-' || *data == '+')
	{
		if (*data == '-')
			signe = -1;
		data++;
	}
	while ((ft_isdigit(*data)))
		res = res * 10 + (*data++ - '0');
	data++;
	while ((ft_isdigit(*data)))
	{
		res2 = res2 * 10 + (*data++ - '0');
		i *= 10;
	}
	res2 = res2 / i;
	return ((res2 + res) * signe);
}

int	check_args(int ac, char **args, t_fractol *fractol)
{
	if (ac == 2)
	{
		if (!ft_strcmp("Mandelbrot", args[1]))
			fractol->name = "m";
		else if (!ft_strcmp("Julia", args[1]))
			fractol->name = "j";
		else
			close_fract_v2();
	}
	else if (ac == 4 && !ft_strcmp("Julia", args[1])
		&& is_valid(args[2]) && is_valid(args[3]))
	{
		fractol->julia.r = ft_atod(args[2]);
		fractol->julia.i = ft_atod(args[3]);
		fractol->name = "j";
		return (0);
	}
	else
	{
		close_fract_v2();
	}
	return (0);
}

void	close_fract(t_fractol *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->mlx_img.ptr);
	mlx_destroy_window(fractol->mlx, fractol->mlx_win);
	exit(0);
}
