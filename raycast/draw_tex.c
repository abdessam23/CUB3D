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

void draw_W_E(t_game *game, t_player *player, int column)
{
    int y = player->start_draw;
    int texX, texY;
    float step, texPos;
    int texHeight;
    unsigned char *texAddr;
    int bpp, lineLen;

    if (player->raydiX > 0)
    {
        texX = (int)(player->wallX * game->west_width);
        if ((player->side == 0 && player->raydiX > 0) || (player->side == 1 && player->raydiY < 0))
            texX = game->west_width - 1 - texX;
        texHeight = game->west_height;
        texAddr = (unsigned char *)game->west_addr;
        bpp = game->west_bpp / 8;
        lineLen = game->west_line_len;
    }
    else
    {
        texX = (int)(player->wallX * game->east_width);
        texHeight = game->east_height;
        texAddr = (unsigned char *)game->east_addr;
        bpp = game->east_bpp / 8;
        lineLen = game->east_line_len;
    }

    step = (float)texHeight / player->line_height;
    texPos = (player->start_draw - WIN_HEIGHT / 2 + player->line_height / 2) * step;

    while (y < player->end_draw)
    {
        texY = (int)texPos;
        if (texY >= texHeight) texY = texHeight - 1;
        texPos += step;

        unsigned int color = *(unsigned int *)(texAddr + texY * lineLen + texX * bpp);
        put_pixel(&game->img, column, y, color);
        y++;
    }
}

void draw_N_S(t_game *game, t_player *player, int column)
{
    int y = player->start_draw;
    int texX, texY;
    float step, texPos;
    int texHeight;
    unsigned char *texAddr;
    int bpp, lineLen;

    if (player->raydiY > 0)
    {
        texX = (int)(player->wallX * game->north_width);
        texHeight = game->north_height;
        texAddr = (unsigned char *)game->north_addr;
        bpp = game->north_bpp / 8;
        lineLen = game->north_line_len;
    }
    else
    {
        texX = (int)(player->wallX * game->south_width);
        if ((player->side == 0 && player->raydiX > 0) || (player->side == 1 && player->raydiY < 0))
            texX = game->south_width - 1 - texX;
        texHeight = game->south_height;
        texAddr = (unsigned char *)game->south_addr;
        bpp = game->south_bpp / 8;
        lineLen = game->south_line_len;
    }

    step = (float)texHeight / player->line_height;
    texPos = (player->start_draw - WIN_HEIGHT / 2 + player->line_height / 2) * step;

    while (y < player->end_draw)
    {
        texY = (int)texPos;
        if (texY >= texHeight) texY = texHeight - 1;
        texPos += step;

        unsigned int color = *(unsigned int *)(texAddr + texY * lineLen + texX * bpp);
        put_pixel(&game->img, column, y, color);
        y++;
    }
}



/*void	draw_W_E(t_game *game, t_player *player, int column)*/
/*{*/
/*	int	texX;*/
/*	int	texY; */
/*	int	y;*/
/**/
/*	y = player->start_draw;*/
/*	if (player->raydiX > 0)*/
/*	{*/
/*		texX = (int)(player->wallX * game->west_width);*/
/*		if ((player->side == 0 && player->raydiX > 0) || (player->side == 1 && player->raydiY < 0))*/
/*			texX = game->west_width - 1 - texX;*/
/*		while (y < player->end_draw)*/
/*		{*/
/*			texY = (int)(((y - player->start_draw) * game->west_height) / player->line_height);*/
/*			unsigned int color = *(unsigned int *)(game->west_addr + texY * game->west_line_len + texX * (game->west_bpp / 8));*/
/*			put_pixel(&game->img, column, y, color);*/
/*			y++;*/
/*		}*/
/*	}*/
/*	else*/
/*{*/
/*		texX = (int)(player->wallX * game->east_width);*/
/*		while (y < player->end_draw)*/
/*		{*/
/*			texY = (int)(((y - player->start_draw) * game->east_height) / player->line_height);*/
/*			unsigned int color = *(unsigned int *)(game->east_addr + texY * game->east_line_len + texX * (game->east_bpp / 8));*/
/*			put_pixel(&game->img, column, y, color);*/
/*			y++;*/
/*		}*/
/*	}*/
/*}*/
/**/
/*void	draw_N_S(t_game *game, t_player *player, int column)*/
/*{*/
/*	int	texX;*/
/*	int	texY; */
/*	int	y;*/
/**/
/*	y = player->start_draw;*/
/*	if (player->raydiY > 0)*/
/*	{*/
/*		texX = (int)(player->wallX * game->north_width);*/
/*		while (y < player->end_draw)*/
/*		{*/
/*			texY = (int)(((y - player->start_draw) * game->north_height) / player->line_height);*/
/*			unsigned int color = *(unsigned int *)(game->north_addr + texY * game->north_line_len + texX * (game->north_bpp / 8));*/
/*			put_pixel(&game->img, column, y, color);*/
/*			y++;*/
/*		}*/
/*	}*/
/*	else*/
/*	{*/
/*		texX = (int)(player->wallX * game->south_width);*/
/*		if ((player->side == 0 && player->raydiX > 0) || (player->side == 1 && player->raydiY < 0))*/
/*			texX = game->south_width - 1 - texX;*/
/*		while (y < player->end_draw)*/
/*		{*/
/*			texY = (int)(((y - player->start_draw) * game->south_height) / player->line_height);*/
/*			unsigned int color = *(unsigned int *)(game->south_addr + texY * game->south_line_len + texX * (game->south_bpp / 8));*/
/*			put_pixel(&game->img, column, y, color);*/
/*			y++;*/
/*		}*/
/*	}*/
/*}*/

void	Draw_textures(t_game *game, t_player *player, int column)
{

	// Draw wall
	if (player->side == 0)
		draw_W_E(game, player, column);
	if (player->side == 1)
		draw_N_S(game, player, column);
}

int	to_hex(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_wall_column(t_game *game, t_player *player, int column)
{
	// get colors
	/*int roof_color = to_hex(player->roof[0], player->roof[1], player->roof[2]);*/
	/*int floor_color = to_hex(player->floor[0], player->floor[1], player->floor[2]);*/
	// Calculate line height and draw positions
	if (player->side == 0)
		player->wallp = player->dsidX - player->dx;
	else
		player->wallp = player->dsidY - player->dy;

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

	// Draw ceiling (above wall)
	for (int y = 0; y < player->start_draw; y++)
		put_pixel(&game->img, column, y, 0x8BE9FF);

	Draw_textures(game, player, column);

	// Draw floor (below wall)
	for (int y = player->end_draw; y < WIN_HEIGHT; y++)
		put_pixel(&game->img, column, y, 0xB7715C);
}
