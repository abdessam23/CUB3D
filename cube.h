#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "mlx.h"

#define WIN_WIDTH 1000
#define	WIN_HEIGHT 800

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
}	t_player;
#endif
