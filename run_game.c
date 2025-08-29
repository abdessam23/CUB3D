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
	int side = 0;
	int hit = 0;
	int *p;
	float wallX;
	int dirX;
	int dirY;
	planeX = 0;
	planeY  = 0.66;
	p = direction(player->direction);
	dirX = p[0];
	dirY = p[1];
	free(p);
	while (!hit)
	{
		for (int i = 0; i < width - 1; i++)
		{
			int mapX = (int)player->playerX;
			int mapY = (int)player->playerY;
			hit = 0;
			cameraX = 2 * i/width - 1;
			raydiX = dirX + planeX * cameraX;
			raydiY = dirY + planeY * cameraX;
			dx = sqrt(1 + (raydiY * raydiY) / (raydiX * raydiX));
			dy = sqrt(1 + (raydiX * raydiX) / (raydiY * raydiY));
			if (raydiX < 0)
			{
				dsidX = (player->playerX - mapX) * dx;
				stepX = -1;
			}
			else
			{
				dsidX = (mapX + 1.0 - player->playerX) * dx;
				stepX = 1;
			}
			if (raydiY < 0)
			{
				dsidY = (player->playerY - mapY) * dy;
				stepY = -1;
			}
			else
			{
				dsidY = (mapY + 1.0 - player->playerY) * dy;
				stepY = 1;
			}
			while (!hit)
			{
				if (dsidX < dsidY)
				{
					dsidX += dx;
					mapX += stepX;
					side = 0;
				}
				else
				{
					dsidY += dy;
					mapY += stepY;
					side = 1;
				}
				if (mapX < 0 || mapX >= WIDTH || mapY < 0 || mapY >= HEIGHT)
					break;
				if (player->map[mapX][mapY] == '1') // we need map here!!
					hit = 1;
			}
			if (side == 0)
				wallp = dsidX - dx;
			else
				wallp = dsidY - dy;
			line_hight = (int)HEIGHT/wallp;
			int startdraw = HEIGHT/2 - line_hight/2;
			if (startdraw < 0)
				startdraw = 0;
			int enddraw = HEIGHT/2 + line_hight/2;
			if (enddraw >= HEIGHT)
				enddraw = HEIGHT - 1;
			if (side == 0)
				wallX = player->playerY + wallp * raydiY;
			else
				wallX = player->playerX + wallp * raydiX;
			wallX -= floor(wallX);
			int texX = (int) wallX * 64;
		}
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
