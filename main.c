
#include "fractol.h"
#include <stdlib.h>
// f(z) == z**2 + c ;
// (x + yi) * (x +yi) == x*x + xyi + xyi - y*y
// x*x - y*y + 2xyi ==> a = x*x - y*y; b = 2xy;
void print_complex(t_complex n) {
  printf(" real == %f , imaginary == %f\n", n.r, n.i);
}
void my_mlx_pixel_put(t_img *data, int x, int y, int color) {
  char *dst;

  dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
  *(unsigned int *)dst = color;
}
double ft_scale(double num, double new_min, double new_max, double old_min,
                double old_max) {
  return (new_max - new_min) * (num - old_min) / (old_max - old_min) + new_min;
}
t_fractol *get_fractol() {
  static t_fractol fractol;
  return &fractol;
}

void change_window_center(double *max_x, double *max_y, double *min_x,
                          double *min_y, double new_center_x,
                          double new_center_y) {
  double width = *max_x - *min_x;
  double height = *max_y - *min_y;

  *max_x = new_center_x + width / 2;
  *max_y = new_center_y + height / 2;
  *min_x = new_center_x - width / 2;
  *min_y = new_center_y - height / 2;
}

int mandelbrot_fun(t_complex c) {
  t_complex z;
  t_complex tmp;
  z.r = 0;
  z.i = 0;
  int max_i = get_fractol()->max_iter;
  while (max_i > 0 &&
         z.r * z.r + z.i * z.i <
             4) // todo create a function and put this logic inside it
  {
    tmp.r = z.r * z.r - (z.i * z.i);
    z.i = 2 * z.r * z.i;
    z.r = tmp.r;
    z.r = z.r + c.r;
    z.i = z.i + c.i;
    max_i--;
  }
  if (max_i == 0)
    return 0x00;
  return ft_scale(get_fractol()->max_iter - max_i, 0x00000000, 0x00FFFFFF, 0,
                  max_i);
}
void render_pixels(t_fractol *fractol) {
  t_complex tmp;
  int i = 0;
  int x = 0;
  int y = 0;
  //mlx_clear_window(fractol->mlx, fractol->mlx_win);
  while (i < WIDTH * HEIGHT) {
    x = i / HEIGHT;
    y = i % HEIGHT;
    tmp.r = (ft_scale(x, -2, 2, 0, WIDTH * fractol->zoom) + fractol->shift_x);
    tmp.i = (ft_scale(y, -2, 2, 0, HEIGHT * fractol->zoom) +
             fractol->shift_y); // todo add shift_y
    my_mlx_pixel_put(&fractol->mlx_img, x, y, mandelbrot_fun(tmp));
    i++;
  }
  mlx_put_image_to_window(fractol->mlx, fractol->mlx_win, fractol->mlx_img.ptr,
                          0, 0);
}
void close_fract() {
  t_fractol *fractol;
  fractol = get_fractol();
  if (fractol->mlx_img.ptr)
    mlx_destroy_image(fractol->mlx, fractol->mlx_img.ptr);
  if (fractol->mlx_win)
    mlx_destroy_window(fractol->mlx, fractol->mlx_win);
  if (fractol->mlx)
    free(fractol->mlx);
  exit(0);
}
int mouse_hook(int keycode, t_fractol *param) {
  int x;
  int y;
  t_complex pos;
  (void)param;
  printf("the code clicked is = %d\n", keycode);
  if (keycode == 1) {
    mlx_mouse_get_pos(get_fractol()->mlx_win, &x, &y);
    pos.r = ft_scale(x, -2, 2, 0, WIDTH);
    pos.i = ft_scale(y, -2, 2, 0, HEIGHT);
    printf("mouse === %d ,%d )", x, y);
    printf("mousez === %f ,%f )", pos.r, y);
  }
  return 0;
}
int key_hook(int keycode, void *param) {
  printf("the code clicked is = %d\n", keycode);
  t_fractol *fractol = param;
  int x;
  int y;
  if (keycode == 126 || keycode == 125 || keycode == 123 || keycode == 124 ||
      keycode == 13 || keycode == 1) {
    if (keycode == 126)
      get_fractol()->shift_y -= 0.5 / fractol->zoom;
    if (keycode == 125)
      get_fractol()->shift_y += 0.5 / fractol->zoom;
    if (keycode == 123)
      get_fractol()->shift_x -= 0.5 / fractol->zoom;
    if (keycode == 124)
      get_fractol()->shift_x += 0.5 / fractol->zoom;
    if (keycode == 13)
      get_fractol()->zoom *= 1.05;
    if (keycode == 1)
      get_fractol()->zoom *= 0.95;
    printf("zoom == %f\n", get_fractol()->zoom);
    printf("shift-x == %f\n", get_fractol()->shift_x);
    render_pixels(fractol);
  }
  if (keycode == 53)
    close_fract();
  return 0;
}
int main() {
  t_fractol *fractol;
  fractol = get_fractol();
  fractol->zoom = 1;
  fractol->max_iter = MAX_ITERATIONS;
  fractol->mlx = mlx_init();
  fractol->mlx_win = mlx_new_window(fractol->mlx, WIDTH, HEIGHT, "hello");
  fractol->mlx_img.ptr = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
  fractol->mlx_img.addr = mlx_get_data_addr(
      fractol->mlx_img.ptr, &fractol->mlx_img.bits_per_pixel,
      &fractol->mlx_img.line_length, &fractol->mlx_img.endian);
  render_pixels(fractol);
  mlx_key_hook(fractol->mlx_win, key_hook, fractol);
  mlx_mouse_hook(fractol->mlx_win, mouse_hook, fractol);
  mlx_loop(fractol->mlx);
}
