/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:22:27 by asyani            #+#    #+#             */
/*   Updated: 2025/09/02 18:42:02 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float *direction(char c)
{
	float *p = malloc(sizeof(int) * 2);
	if (c == 'N' || c == 'S')
	{
		p[0] = 0;
		if (c == 'N')
			p[1] = -1;
		else
			p[1] = 1;
		return p;
	}
	if (c == 'E' || c == 'W')
	{
		p[1] = 0;
		if (c == 'W')
			p[0] = -1;
		else
			p[0] = 1;
		return p;
	}
	return 0;
}

void	set_plane(t_player *player)
{
	if (player->direction == 'N')
	{
		player->planeX = 0.66;
		player->planeY = 0;
	}
	else if (player->direction == 'S')
	{
		player->planeX = -0.66;
		player->planeY = 0;
	}
	else if (player->direction == 'E')
	{
		player->planeX = 0;
		player->planeY = 0.66;
	}
	else if (player->direction == 'W')
	{
		player->planeX = 0;
		player->planeY = -0.66;
	}
}

void	calc_step(t_player *player)
{
	// Calculate step and initial sideDist
	if (player->raydiX < 0)
	{
		player->stepX = -1;
		player->dsidX = (player->playerX - player->mapX) * player->dx;
	}
	else
	{
		player->stepX = 1;
		player->dsidX = (player->mapX + 1.0 - player->playerX) * player->dx;
	}
	if (player->raydiY < 0)
	{
		player->stepY = -1;
		player->dsidY = (player->playerY - player->mapY) * player->dy;
	}
	else
	{
		player->stepY = 1;
		player->dsidY = (player->mapY + 1.0 - player->playerY) * player->dy;
	}
}

void	DDA_algo(t_player *player)
{
	while (!player->hit)
	{
		if (player->dsidX < player->dsidY)
		{
			player->dsidX += player->dx;
			player->mapX += player->stepX;
			player->side = 0;
		}
		else
	{
			player->dsidY += player->dy;
			player->mapY += player->stepY;
			player->side = 1;
		}
		if (player->map[player->mapY][player->mapX] == '1')
			player->hit = 1;
	}
}


void	prep_calcs(t_player *player, int i)
{
	player->mapX = (int)player->playerX;
	player->mapY = (int)player->playerY;

	player->hit = 0;
	player->cameraX = 2 * (float)i / WIN_WIDTH - 1;
	player->raydiX = player->dirX + player->planeX * player->cameraX;
	player->raydiY = player->dirY + player->planeY * player->cameraX;

	// Calculate delta distances
	if (player->raydiX == 0)
		player->dx = 1e30;
	else
		player->dx = fabs(1 / player->raydiX);

	if (player->raydiY == 0)
		player->dy = 1e30;
	else
		player->dy = fabs(1 / player->raydiY);
}

void	put_pixel(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void	wall_calc(t_player *player)
{
	// Calculate wall distance
	if (player->side == 0)
		player->wallp = player->dsidX - player->dx;
	else
		player->wallp = player->dsidY - player->dy;

	// Calculate line height and draw positions
	player->line_hight = (int)(WIN_HEIGHT / player->wallp);
	int startdraw = WIN_HEIGHT / 2 - player->line_hight / 2;
	if (startdraw < 0)
		startdraw = 0;
	int enddraw = WIN_HEIGHT / 2 + player->line_hight / 2;
	if (enddraw >= WIN_HEIGHT)
		enddraw = WIN_HEIGHT - 1;

	// Calculate wall texture coordinate
	if (player->side == 0)
		player->wallX = player->playerY + player->wallp * player->raydiY;
	else
		player->wallX = player->playerX + player->wallp * player->raydiX;
	player->wallX -= floor(player->wallX);
	player->texX = (int)(player->wallX * 64);
}

void	draw_wall_column(t_game *game, t_player *player, int column)
{
	// Calculate line height and draw positions
	if (player->side == 0)
		player->wallp = player->dsidX - player->dx;
	else
		player->wallp = player->dsidY - player->dy;

	int line_height = (int)(WIN_HEIGHT / player->wallp);
	int start_draw = WIN_HEIGHT / 2 - line_height / 2;
	int end_draw = WIN_HEIGHT / 2 + line_height / 2;

	if (start_draw < 0)
		start_draw = 0;
	if (end_draw >= WIN_HEIGHT)
		end_draw = WIN_HEIGHT - 1;

	// Choose wall color based on side
	int color;
	if (player->side == 0)
		color = 0xA16B10;  // red for North/South walls
	else
		color = 0x0A7A31;  // Green for East/West walls

	// Draw ceiling (above wall)
	for (int y = 0; y < start_draw; y++)
		put_pixel(&game->img, column, y, 0x87CEEB);

	// Draw wall
	for (int y = start_draw; y < end_draw; y++)
		put_pixel(&game->img, column, y, color);

	// Draw floor (below wall)
	for (int y = end_draw; y < WIN_HEIGHT; y++)
		put_pixel(&game->img, column, y, 0xff0000);
}


void	run_game(t_player *player, t_game *game)
{
	// Cast rays for each column
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		prep_calcs(player, i);
		calc_step(player);
		DDA_algo(player);
		//wall_calc(player);
		draw_wall_column(game, player, i);
	}
}
int key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode < 65536)
		game->keys[keycode] = 1;
	return (0);
}

int key_release(int keycode, t_game *game)
{
	if (keycode < 65536)
		game->keys[keycode] = 0;
	return (0);
}

void rotate_player(t_player *player, float angle)
{
	// Rotate direction vector
	float oldDirX = player->dirX;
	player->dirX = player->dirX * cos(angle) - player->dirY * sin(angle);
	player->dirY = oldDirX * sin(angle) + player->dirY * cos(angle);
	

	//Rotate plane vector
	float oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(angle) - player->planeY * sin(angle);
	player->planeY = oldPlaneX * sin(angle) + player->planeY * cos(angle);	
}


void handle_movement(t_game *game)
{
	t_player *player;
	
	
	
	player = game->player;
	// Rotation (Left/Right arrows or A/D keys)
	if (game->keys[KEY_LEFT] || game->keys[KEY_A])
		rotate_player(player, -ROT_SPEED);

	if (game->keys[KEY_RIGHT] || game->keys[KEY_D])
		rotate_player(player, ROT_SPEED);

	// Forward movement (W key)
	if (game->keys[KEY_W] || game->keys[KEY_UP])
	{
		float newX = player->playerX + player->dirX * MOVE_SPEED;
		float newY = player->playerY + player->dirY * MOVE_SPEED;

		// Check collision with walls
		if (player->map[(int)newY][(int)player->playerX] != '1')
			player->playerY = newY;
		if (player->map[(int)player->playerY][(int)newX] != '1')
			player->playerX = newX;
	}

	// Backward movement (S key)
	if (game->keys[KEY_S] || game->keys[KEY_DOWN])
	{
		float newX = player->playerX - player->dirX * MOVE_SPEED;
		float newY = player->playerY - player->dirY * MOVE_SPEED;

		// Check collision with walls
		if (player->map[(int)newY][(int)player->playerX] != '1')
			player->playerY = newY;
		if (player->map[(int)player->playerY][(int)newX] != '1')
			player->playerX = newX;
	}
}

void	init_player_direction(t_player *player)
{
	// Get initial direction
	float *p = direction(player->direction);
	if (!p)
	{
		printf("Yes");
		return;
	}
	player->dirX = p[0];
	player->dirY = p[1];
	free(p);

	// Set plane vector
	set_plane(player);
}

void	init_player(t_player *player)
{
	player->map = create_test_map();
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 30; x++)
		{
			if (player->map[y][x] == 'N')
       			{
				printf("find N in %d,%d\n", y, x);
				player->direction = 'N';
				player->playerY = (float)y;
				player->playerX = (float)x;
			}
			else if (player->map[y][x] == 'W')
       			{
				printf("find W in %d,%d\n", y, x);
				player->playerY = (float)y;
				player->playerX = (float)x;
				player->direction = 'W';
			}
			else if (player->map[y][x] == 'E')
       			{
				printf("find E in %d,%d\n", y, x);
				player->playerY = (float)y;
				player->playerX = (float)x;
				player->direction = 'E';
			}
       			else if (player->map[y][x] == 'S')
			{
				printf("find S in %d,%d\n", y, x);
				player->direction = 'S';
				player->playerY = (float)y;
				player->playerX = (float)x;
			}
		}
	}
	init_player_direction(player);
}

int game_loop(t_game *game)
{
	handle_movement(game);
	render_frame(game);
	return (0);
}

void	render_frame(t_game *game)
{
	run_game(game->player, game);
	mlx_put_image_to_window(game->mlx, game->mlx_window, game->img.img, 0, 0);
}

int	close_window(t_game *game)
{
	exit(0);
	return (0);
}


int init_cube(void)
{
	t_game      game;
	t_player    player;
	int         i;

	// Initialize key states
	i = 0;
	while (i < 65536)
	{
		game.keys[i] = 0;
		i++;
	}

	// Initialize player
	init_player(&player);

	// Initialize MLX
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);

	game.mlx_window = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game.mlx_window)
		return (1);

	// Create image
	game.img.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel, 
				   &game.img.line_length, &game.img.endian);

	game.player = &player;

	// Set up event hooks
	mlx_hook(game.mlx_window, 2, 1L<<0, key_press, &game);
	mlx_hook(game.mlx_window, 3, 1L<<1, key_release, &game);
	mlx_hook(game.mlx_window, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);

	mlx_loop(game.mlx);
	return (0);
}

char	**create_test_map(void)
{
	char **map = malloc(sizeof(char*) * 10);

	map[0] = strdup("111111111111111111111111111111");
	map[1] = strdup("100001000000000000000001000001");
	map[2] = strdup("100000000000000000000000000001");
	map[3] = strdup("101000000100000001011110000001");
	map[4] = strdup("100000010000000001000000000001");
	map[5] = strdup("100000000000000000111100000001");
	map[6] = strdup("100001000000000000000000000001");
	map[7] = strdup("100000000000N00001000000001001");
	map[8] = strdup("100000111100000001000000000001");
	map[9] = strdup("111111111111111111111111111111");

	return (map);
}

int main()
{
	return (init_cube());
}
