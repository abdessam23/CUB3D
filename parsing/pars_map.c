/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:58:53 by abdo              #+#    #+#             */
/*   Updated: 2025/10/02 18:45:44 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_arg(char *s)
{
	char	*str;

	str = ft_strrchr(s, '.');
	if (ft_strlen(str) > 4)
		return (-1);
	if (ft_strncmp(str, ".cub", 4) == 0)
		return (1);
	return (-1);
}

int	check_inside_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && is_valid(str[i]) && str[i] != '\n')
			i++;
		if (str[i] != '\0' && str[i] != '\n' && !is_valid(str[i]))
			return (0);
		if (str[i] == '\0')
			break ;
		i++;
		if (str[i] == '\n')
		{
			while (str[i] && ft_whitespace(str[i]))
				i++;
			if (str[i] == '\0')
				return (1);
			return (0);
		}
	}
	return (1);
}

int	ft_valid_map(char **map, t_player *player)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		if (!ft_valid_id(map[i], player))
		{
			printf("Error: identifier\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	pars_fun(int argc, char **argv, t_player *player)
{
	char	*str;
	char	**map;
	player->northimg = NULL;
	player->southimg = NULL;
	player->eastimg = NULL;
	player->westimg = NULL;
	player->map = NULL;

	if (argc != 2)
		return (1);
	if (check_arg(argv[1]) == -1)
	{
		printf("Error\n");
		return (1);
	}
	str = read_line(argv[1]);
	if (!str || !check_map(str))
	{
		printf("Error: unexcepted in map\n");
		return (1);
	}
	map = ft_split(str, '\n');
	free(str);
	if (!map)
		return (1);
	if (!ft_valid_map(map, player) || !check_in_map(map, player))
	{
		printf("Error: inside map!\n");
		return (1);
	}
	for (int i = 0; map[i] != NULL; i++)
	{
		free(map[i]);
	}
	free(map);
	return (0);
}
