#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "./libft/libft.h"
#include "mlx.h"

#define PI	3.14159265358979323846
#define WIN_WIDTH 1000
#define	WIN_HEIGHT 800
#define	FOV 66.0
#define V_RAD (VIEW * PI / 180.0)

typedef struct s_game
{
	void	*mlx;
	void	*mlx_window;
}	t_game;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_player
{
	char	**map;
	double	playerX;
	double	playerY;
	float cameraX;
	float planeX;
	float planeY;
	float raydiX;
	float raydiY;
	double dx;
	double dy;
	double dsidX;
	double dsidY;
	double stepX;
	double stepY;
	double wallp;
	int line_hight;
	int side;
	int hit;
	int *p;
	float wallX;
	int dirX;
	int dirY;
	int	texX;
}	t_player;
#endif
