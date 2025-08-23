/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyani <asyani@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 09:55:43 by asyani            #+#    #+#             */
/*   Updated: 2025/08/10 20:10:46 by asyani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	get_player_pos(t_player *player)
{
	int	x;
	int	y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[y])
		{
			if (map[x][y] == 'P')
			{
				player->x = map[x];
				player->y = map[y];
			}
			y++;
		}
		x++;
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
	get_player_pos(&player);
}
