/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 13:00:18 by asyani            #+#    #+#             */
/*   Updated: 2025/08/30 13:01:43 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	key_down(t_game *game, t_player *player)
{
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
	key_down(game, player);
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
