/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:58:53 by abdo              #+#    #+#             */
/*   Updated: 2025/10/02 10:53:47 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_arg(char *s)
{
	char *str;

	str = ft_strrchr(s, '.');
	if (strcmp(str, ".cub") == 0)
		return (1);
	return (-1);
}

int	check_inside_map(char *str)
{
	int i;

	i = 0;
	while (*str)
	{
		while (is_valid(*str) && *str != '\n')
			str++;
		if (*str != '\0' && *str != '\n' && !is_valid(*str))
		{
			printf("%c :9issue inside map\n", *str);
			return (0);
		}
		str++;
		if (*str == '\n')
		{
			while (*str && ft_whitespace(*str))
				str++;
			if (*str == '\0')
				return (1);
			printf("issue inside map\n");
			return (0);
		}
	}
	return (1);
}

int	ft_valid_map(char **map, t_player *player)
{
	int i;

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
	char *str;
	char **map;

	if (argc != 2)
		return (1);
	if (check_arg(argv[1]) == -1)
	{
		printf("Error\n");
		return (1);
	}
	str = read_line(argv[1]);
	printf("%s \n", str);
	if (!check_map(str))
	{
		printf("Error: unexcepted in map\n");
		return (1);
	}
	map = ft_split(str, '\n');
	if (!map)
		return (1);
	if (!ft_valid_map(map, player) || !check_in_map(map, player))
		return (1);
	return (0);
}