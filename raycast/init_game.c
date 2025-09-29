/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 09:40:56 by asyani            #+#    #+#             */
/*   Updated: 2025/09/29 18:18:51 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int init_cube(t_player *player)
{
	t_game      game;
	   for(int i = 0; player->map[i] ;i++)
    {
        printf("%s\n", player->map[i]);
    }
	int         i;

	// Initialize key states
	i = 0;
	while (i < 65536)
	{
		game.keys[i] = 0;
		i++;
	}
	// Initialize player
	init_player_direction(player);
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
	game.player = player;
	load_textures(&game);
	// Set up event hooks
	mlx_hook(game.mlx_window, 2, 1L<<0, key_press, &game);
	mlx_hook(game.mlx_window, 3, 1L<<1, key_release, &game);
	mlx_hook(game.mlx_window, 17, 0, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

void	load_textures(t_game *game)
{
	game->north_img = mlx_xpm_file_to_image(game->mlx, game->player->northimg,
					&game->north_width, &game->north_height);
	game->south_img = mlx_xpm_file_to_image(game->mlx, game->player->southimg,
					&game->south_width, &game->south_height);
	game->west_img = mlx_xpm_file_to_image(game->mlx,game->player->westimg,
					&game->west_width, &game->west_height);
	game->east_img = mlx_xpm_file_to_image(game->mlx, game->player->eastimg,
					&game->east_width, &game->east_height);
	if (!game->north_img || !game->south_img || !game->west_img || !game->east_img){
		printf("hello");
		exit(1);
	}
		
	game->north_addr = mlx_get_data_addr(game->north_img,
                                   &game->north_bpp, &game->north_line_len, &game->north_endian);
	game->south_addr = mlx_get_data_addr(game->south_img,
                                   &game->south_bpp, &game->south_line_len, &game->south_endian);
	game->west_addr = mlx_get_data_addr(game->west_img,
                                   &game->west_bpp, &game->west_line_len, &game->west_endian);
	game->east_addr = mlx_get_data_addr(game->east_img,
                                   &game->east_bpp, &game->east_line_len, &game->east_endian);
	if (!game->north_addr || !game->south_addr || !game->west_addr || !game->east_addr)
		return ;
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

// void	init_player(t_player *player)
// {
// 	player->map = create_test_map();
// 	for (int y = 0; y < 10; y++)
// 	{
// 		for (int x = 0; x < 30; x++)
// 		{
// 			if (player->map[y][x] == 'N')
//        			{
// 				player->direction = 'N';
// 				player->playerY = (float)y;
// 				player->playerX = (float)x;
// 			}
// 			else if (player->map[y][x] == 'W')
//        			{
// 				player->playerY = (float)y;
// 				player->playerX = (float)x;
// 				player->direction = 'W';
// 			}
// 			else if (player->map[y][x] == 'E')
//        			{
// 				player->playerY = (float)y;
// 				player->playerX = (float)x;
// 				player->direction = 'E';
// 			}
//        			else if (player->map[y][x] == 'S')
// 			{
// 				player->direction = 'S';
// 				player->playerY = (float)y;
// 				player->playerX = (float)x;
// 			}
// 		}
// 	}
// 	init_player_direction(player);
// }
