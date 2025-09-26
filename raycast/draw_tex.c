/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:47:08 by asyani            #+#    #+#             */
/*   Updated: 2025/09/20 09:47:22 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	side_W_E(t_player *player, t_game *game)
{
		if (player->raydiX > 0)
		{ 
			// West wall
			player->texWidth = game->west_width;
			player->texHeight = game->west_height;
			player->texAddr = (unsigned char *)game->west_addr;
			player->bpp = game->west_bpp / 8;
			player->lineLen = game->west_line_len;
		}
		else
		{ 
			// East wall
			player->texWidth = game->east_width;
			player->texHeight = game->east_height;
			player->texAddr = (unsigned char *)game->east_addr;
			player->bpp = game->east_bpp / 8;
			player->lineLen = game->east_line_len;
		}
}

void	side_N_S(t_player *player, t_game *game)
{
		if (player->raydiY > 0)
		{ // North wall
			player->texWidth = game->north_width;
			player->texHeight = game->north_height;
			player->texAddr = (unsigned char *)game->north_addr;
			player->bpp = game->north_bpp / 8;
			player->lineLen = game->north_line_len;
		}
		else
		{ // South wall
			player->texWidth = game->south_width;
			player->texHeight = game->south_height;
			player->texAddr = (unsigned char *)game->south_addr;
			player->bpp = game->south_bpp / 8;
			player->lineLen = game->south_line_len;
		}
}

void draw_wall(t_game *game, t_player *player, int column)
{
	int texX;
	int texY;
	int y;

	y = player->start_draw;
	if (player->side == 0)
		side_W_E(player, game);
	else
		side_N_S(player, game);
	texX = (int)(player->wallX * player->texWidth);
	if ((player->side == 0 && player->raydiX > 0) ||
		(player->side == 1 && player->raydiY < 0))
		texX = player->texWidth - texX - 1;
	player->step = (float)player->texHeight / player->line_height;
	player->texPos = (player->start_draw - WIN_HEIGHT / 2.0f + player->line_height / 2.0f) * player->step;
	while (y < player->end_draw)
	{
		texY = (int)player->texPos;
		if (texY >= player->texHeight) texY = player->texHeight - 1;
		player->texPos += player->step;

		unsigned int color = *(unsigned int *)(player->texAddr + texY * player->lineLen + texX * player->bpp);
		put_pixel(&game->img, column, y, color);
		y++;
	}
}

int	to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	wall_height(t_player *player)
{
	player->line_height = (int)(WIN_HEIGHT / player->wallp);
	player->start_draw = WIN_HEIGHT / 2 - player->line_height / 2;
	player->end_draw = WIN_HEIGHT / 2 + player->line_height / 2;

	if (player->start_draw < 0)
		player->start_draw = 0;
	if (player->end_draw >= WIN_HEIGHT)
		player->end_draw = WIN_HEIGHT - 1;


	if (player->side == 0)
		player->wallX = player->playerY + player->wallp * player->raydiY;
	else
		player->wallX = player->playerX + player->wallp * player->raydiX;
	player->wallX -= floor(player->wallX);
}

void	draw_wall_column(t_game *game, t_player *player, int column)
{
	int	y;
	// get colors
	/*int roof_color = to_hex(player->roof[0], player->roof[1], player->roof[2]);*/
	/*int floor_color = to_hex(player->floor[0], player->floor[1], player->floor[2]);*/
	// Calculate line height and draw positions
	if (player->side == 0)
		player->wallp = player->dsidX - player->dx;
	else
		player->wallp = player->dsidY - player->dy;
	wall_height(player);

	// Draw ceiling (above wall)
	y = 0;
	while (y < player->start_draw)
	{
		put_pixel(&game->img, column, y, 0x8BE9FF);
		y++;
	}
	draw_wall(game, player, column);
	// Draw floor (below wall)
	y = player->end_draw;
	while (y < WIN_HEIGHT)
	{
		put_pixel(&game->img, column, y, 0xB7715C);
		y++;
	}
}
