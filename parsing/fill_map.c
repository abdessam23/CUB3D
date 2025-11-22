/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 12:03:35 by abdo              #+#    #+#             */
/*   Updated: 2025/10/04 12:59:12 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_zero(char **map, int i, int j)
{
	char	up;
	char	down;

	if (map[i][j] != '0')
		return (1);
	up = safe_char_at(map, i - 1, j, '\0');
	down = safe_char_at(map, i + 1, j, '\0');
	if (up == '\0' || down == '\0')
		return (0);
	return (1);
}

void	fill_map(char **str, t_player *player)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
		i++;
	player->map = malloc(sizeof(char *) * (i + 1));
	if (!player->map)
		return ;
	len = i;
	i = 0;
	while (i < len)
	{
		player->map[i] = ft_strdup(str[i]);
		i++;
	}
	player->map[i] = NULL;
	player->map[(int)player->player_y][(int)player->player_x] = '0';
}

void	ft_free_path(t_player *player)
{
	if (player->northimg)
		free(player->northimg);
	if (player->westimg)
		free(player->westimg);
	if (player->southimg)
		free(player->southimg);
	if (player->eastimg)
		free(player->eastimg);
}
