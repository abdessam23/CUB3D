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

int	init_cube(void)
{
	t_game	gm;
	t_data	img;

	gm.mlx = mlx_init();
	gm.mlx_window = mlx_new_window(gm.mlx, MAX_WIDTH, MAX_HEIGHT, "cube3d");
	img.img = mlx_new_image(gm.mlx, 800, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
}
