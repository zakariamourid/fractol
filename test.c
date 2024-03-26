#include <unistd.h>
#include <stdio.h>
#include "mlx.h"
#include "fractol.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    printf("address 2= %p\n",data->addr);
    *(unsigned int*)dst = color;
}
void	my_mlx_pixel_put2(t_img *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int main()
{
    void *mlx = mlx_init();
    void *mlx_win = mlx_new_window(mlx,500,500,"bravo");
    t_img img;
    img.ptr = mlx_new_image(mlx,500,500);
    img.addr = mlx_get_data_addr(img.ptr, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
    mlx_put_image_to_window(mlx, mlx_win, img.ptr, 0, 0);
    mlx_loop(mlx);
}