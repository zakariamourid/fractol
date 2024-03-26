#ifndef FRACTOL_H
#define FRACTOL_H

# include <stdio.h>
# include <unistd.h>
# include "mlx.h"
#define WIDTH 900
#define HEIGHT 900
#define MAX_ITERATIONS 42

typedef struct s_complex
{
	double	r;
	double	i;
}			t_complex;

typedef struct	s_img {
    void	*ptr;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}				t_img;

typedef struct s_fractol
{
    void *mlx;
    void *mlx_win;
    t_img mlx_img;
    t_complex pixel;
    int max_iter;
    float shift_x;
} t_fractol;

#endif