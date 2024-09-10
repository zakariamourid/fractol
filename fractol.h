/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmourid <zmourid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:28:19 by zmourid           #+#    #+#             */
/*   Updated: 2024/04/16 16:56:57 by zmourid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# define WIDTH 1000
# define HEIGHT 1000
# define TILE_SIZE 50
# define MAX_ITERATIONS 240

typedef struct s_complex
{
	double		r;
	double		i;
}				t_complex;

typedef struct s_img
{
	void		*ptr;
	char		*addr;
	int			bpp; //bits_per_pixel
	int			ll; //line_length
	int			e; //endian
}				t_img;

typedef struct s_fractol
{
	void		*mlx;
	void		*mlx_win;
	t_img		mlx_img;
	char		*name;
	t_complex	julia;
	int			max_iter;
	double		shift_x;
	double		shift_y;
	double		x_min;
	double		y_min;
	double		zoom;
	t_complex	mouse;
}				t_fractol;
void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
double			ft_scale(double num, double new_min, double new_max,
					double old_max);
int				get_pixel_color(t_fractol *fractol, t_complex pixel,
					char *name);
void			render_fractol(t_fractol *fractol);
int				key_hook(int keycode, t_fractol *fractol);
void			close_fract(t_fractol *fractol);
void			fractol_init2(t_fractol *fractol);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *s);
int				check_args(int ac, char **args, t_fractol *fractol);
double			ft_atod(char *data);
int				is_valid(char *data);
void			close_fract_v2(void);
void			ft_putstr(char *str);

#endif
