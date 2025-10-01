/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:05:49 by asyani            #+#    #+#             */
/*   Updated: 2025/10/01 10:06:20 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

float	*direction(char c)
{
	float	*p;

	p = malloc(sizeof(int) * 2);
	if (c == 'N' || c == 'S')
	{
		p[0] = 0;
		if (c == 'N')
			p[1] = -1;
		else
			p[1] = 1;
		return (p);
	}
	if (c == 'E' || c == 'W')
	{
		p[1] = 0;
		if (c == 'W')
			p[0] = -1;
		else
			p[0] = 1;
		return (p);
	}
	return (0);
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

void	dda_algo(t_player *player)
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
		if (player->map[player->mapY][player->mapX] == '1'
			|| player->map[player->mapY][player->mapX] == ' ')
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
	if (player->raydiX == 0)
		player->dx = 1e30;
	else
		player->dx = fabs(1 / player->raydiX);
	if (player->raydiY == 0)
		player->dy = 1e30;
	else
		player->dy = fabs(1 / player->raydiY);
}
