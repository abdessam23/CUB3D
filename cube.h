#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "mlx.h"

#define M_PI	3.14159265358979323846
#define WIN_WIDTH 1000
#define	WIN_HEIGHT 800
#define	VIEW 60
#define V_RAD (VIEW * M_PI / 180.0f)

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
	float	x;
	float	y;
	float	dirx;
	float	diry;
	float	p_view;
	float	angle;

}	t_player;
#endif
