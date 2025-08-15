#include "./minilibx-linux/mlx.h"
#include <X11/Xlib.h>
#include <math.h>
#include <stdio.h>

#define color 0xFF0000
#define width 500
#define hight 500
#define Pi 3.14159

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bpp;
	int		sl;
	int		endian;
}				t_data;
int max(int n1, int n2)
{
    if (n1 >= n2)
        return n1;
    else
        return n2;
}
void put_pixel(t_data *img,int x, int y)
{
    char *dst;
    // if (y == -1);
    //  return;
    dst = img->addr + (y * img->sl + x * (img->bpp/8));
    *(unsigned int*)dst = color;
}
void init_line(t_data *img, int x0,int y0,int x1,int y1)
{
   int dx = x1- x0;
   int dy = y1 - y0;
   int step = max(fabs(dx),fabs(dy));
   int x_inc = dx / step;
   int y_inc = dy / step;
   int x = x0;
   int y = y0;

    int i = 0;
   while (i < step)
   {
        put_pixel(img, x, y);
        x += x_inc;
        y += y_inc;
        i++;
   }
}
void draw_line(t_data *img)
{
    int x = 90;
    int y = 90;
    int n_x = 90;
    int n_y = 300;
    float angle = Pi/6;
    init_line(img, x,y,n_x,n_y);
    while (angle < Pi/2)
    {
        n_x = (sin(angle) * 210) + n_x;
        n_y = y + (cos(angle) * 210);
        init_line(img, x,y,n_x,n_y);
        angle += angle;
    }
}

int main()
{
    void *mlx;
    void *mlx_window;
    t_data mlx_img;
    

    mlx = mlx_init();

    mlx_window = mlx_new_window(mlx, width, hight, "Cub3d");
    mlx_img.img = mlx_new_image(mlx,500,500);
    mlx_img.addr = mlx_get_data_addr(mlx_img.img,&mlx_img.bpp,&mlx_img.sl,&mlx_img.endian);
    draw_line(&mlx_img);
    mlx_put_image_to_window(mlx,mlx_window, mlx_img.img,0,0);
    mlx_loop(mlx);
}
