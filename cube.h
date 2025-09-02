/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:04:01 by asyani            #+#    #+#             */
/*   Updated: 2025/09/02 11:04:13 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
#define CUBE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "lib_ft/libft.h"
#include "mlx.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MAX_WIDTH 800
#define MAX_HEIGHT 600

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364

// Movement speeds
# define MOVE_SPEED 0.005
# define ROT_SPEED 0.001

#define PI	3.14159265358979323846
#define	FOV 66.0
#define V_RAD (VIEW * PI / 180.0)


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
	char	direction;
	int	mapX;
	int	mapY;
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
	float dirX;
	float dirY;
	int	texX;
}	t_player;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_window;
	t_data	img;
	t_player *player;
	int         keys[65536];
}	t_game;

float    *direction(char c);
void    set_plane(t_player *player);
void    calc_step(t_player *player);
void    DDA_algo(t_player *player);
void    wall_calc(t_player *player);
void    prep_calcs(t_player *player, int i);
void    put_pixel(t_data *img, int x, int y, int color);
void    draw_wall_column(t_game *game, t_player *player, int column);
void    run_game(t_player *player, t_game *game);
void    init_player_direction(t_player *player);
void    init_player(t_player *player);
int     game_loop(t_game *game);
void    render_frame(t_game *game);
int     close_window(t_game *game);
char    **create_test_map(void);
int     init_cube(void);
int     key_press(int keycode, t_game *game);
int     key_release(int keycode, t_game *game);
void    rotate_player(t_player *player, float angle);
void    handle_movement(t_game *game);

#endif
