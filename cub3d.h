/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:04:15 by abdo              #+#    #+#             */
/*   Updated: 2025/09/15 11:19:24 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <math.h>

# define color 0xFF0000
# define width 800
# define hight 800
# define Pi 3.14159

typedef struct s_player
{
    double playerX;
    double playerY;
    char direction;
    char **map;
    int roof[3];
    int floor[3];
    char *northimg;
    char *southimg;
    char *westimg;
    char *eastimg;
} t_player;

#endif