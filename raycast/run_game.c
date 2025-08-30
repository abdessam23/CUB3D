#include "cub3d.h"

int *direction(char c)
{
	int *p = malloc(sizeof(int) * 2);
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


void run_game(t_player *player)
{
	player->side = 0;
	player->hit = 0;
	player->planeX = 0;
	player->planeY  = 0.66;
	player->p = direction(player->direction);
	player->dirX = p[0];
	player->dirY = p[1];
	free(player->p);

	// Set plane vector perpendicular to direction
	if (player->direction == 'N')
	{
		player->planeX = 0;
		player->planeY = -0.66;
	}
	else if (player->direction == 'S')
	{
		player->planeX = 0;
		player->planeY = 0.66;
	}
	else if (player->direction == 'E')
	{
		player->planeX = 0.66;
		player->planeY = 0;
	}
	else if (player->direction == 'W')
	{
		player->planeX = -0.66;
		player->planeY = 0;
	}

	// Cast rays for each column
	for (int i = 0; i < WIN_WIDTH; i++)
	{
		int mapX = (int)player->playerX;
		int mapY = (int)player->playerY;

		player->hit = 0;
		player->cameraX = 2 * (float)i / width - 1;
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

		// Calculate step and initial sideDist
		if (player->raydiX < 0)
		{
			player->stepX = -1;
			player->dsidX = (player->playerX - mapX) * player->dx;
		}
		else
		{
			player->stepX = 1;
			player->dsidX = (mapX + 1.0 - player->playerX) * player->dx;
		}

		if (player->raydiY < 0)
		{
			player->stepY = -1;
			player->dsidY = (player->playerY - mapY) * player->dy;
		}
		else
		{
			player->stepY = 1;
			player->dsidY = (mapY + 1.0 - player->playerY) * player->dy;
		}

		// Perform DDA
		while (!player->hit)
		{
			if (player->dsidX < player->dsidY)
			{
				player->dsidX += player->dx;
				mapX += player->stepX;
				player->side = 0;
			}
			else
			{
				player->dsidY += player->dy;
				mapY += player->stepY;
				player->side = 1;
			}
			if (player->map[mapY][mapX] == '1')
				player->hit = 1;
		}

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

		// draw the vertical line from startdraw to enddraw
		for (int i = startdraw; i < enddraw; i++)
			start_draw(i, startdraw, enddraw, texX, side);
	}
}

int	init_cube(void)
{
	t_game	gm;
	t_data	img;
	t_player	player;

	player.view = V_RAD;
	player.angle = 0;
	gm.mlx = mlx_init();
	gm.mlx_window = mlx_new_window(gm.mlx, MAX_WIDTH, MAX_HEIGHT, "cube3d");
	img.img = mlx_new_image(gm.mlx, 800, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
}
