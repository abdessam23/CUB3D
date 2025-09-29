/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:22:27 by asyani            #+#    #+#             */
/*   Updated: 2025/09/20 10:01:52 by asyani           ###   ########.fr       */
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

void	run_game(t_player *player, t_game *game)
{
	// Cast rays for each column
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		prep_calcs(player, i);
		calc_step(player);
		DDA_algo(player);
		draw_wall_column(game, player, i);
		i++;
	}
}

void rotate_player(t_player *player, float angle)
{
	// Rotate direction vector
	float	oldDirX;
	float	oldPlaneX;

	oldDirX = player->dirX;
	player->dirX = player->dirX * cos(angle) - player->dirY * sin(angle);
	player->dirY = oldDirX * sin(angle) + player->dirY * cos(angle);
	

	//Rotate plane vector
	oldPlaneX = player->planeX;
	player->planeX = player->planeX * cos(angle) - player->planeY * sin(angle);
	player->planeY = oldPlaneX * sin(angle) + player->planeY * cos(angle);	
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

/*char	**create_test_map(void)*/
/*{*/
/*	char **map = malloc(sizeof(char*) * 10);*/
/**/
/*	map[0] = strdup("111111111111111111111111111111");*/
/*	map[1] = strdup("100001000000000000000001000001");*/
/*	map[2] = strdup("100000000100100000000000000001");*/
/*	map[3] = strdup("10100001111D111111011110000001");*/
/*	map[4] = strdup("100000010000000001000000000001");*/
/*	map[5] = strdup("100000010000000001111100000001");*/
/*	map[6] = strdup("100001000000000000000000000001");*/
/*	map[7] = strdup("100000000000N00001000000001001");*/
/*	map[8] = strdup("100000111100000001000000000001");*/
/*	map[9] = strdup("111111111111111111111111111111");*/
/**/
/*	return (map);*/
/*}*/

int main()
{
	return (init_cube());
}
