/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:11:24 by abdo              #+#    #+#             */
/*   Updated: 2025/10/02 16:23:14 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_map(char *s)
{
	int		count;
	char	*str;

	count = 0;
	str = ft_strdup(s);
	while (*str)
	{
		while (*str && ft_whitespace(*str))
			str++;
		if (*str == '\0' || !ft_identif(*str))
			return (0);
		while (*str && *str != '\n')
			str++;
		while (*str && ft_whitespace(*str))
			str++;
		count++;
		if (count == 6)
		{
			if (*str == '1' && check_inside_map(str))
				return (1);
			return (0);
		}
	}
	return (0);
}

int	find_one(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] == '1')
			return (i);
		i++;
	}
	return (0);
}

int	ft_direction(int c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	safe_char_at(char **map, int i, int j)
{
	int	l;
	int	len;

	l = 0;
	while (map[l] != NULL)
		l++;
	if (i < 0 || j < 0 || i >= l)
		return (' ');
	len = ft_strlen(map[i]);
	if (j >= len)
		return (' ');
	return (map[i][j]);
}

int	check_spaces(char **map, int i, int j)
{
	char	up;
	char	down;
	char	left;
	char	right;

	up = safe_char_at(map, i - 1, j);
	down = safe_char_at(map, i + 1, j);
	left = safe_char_at(map, i, j - 1);
	right = safe_char_at(map, i, j + 1);
	if ((up == '1' || up == ' ') && (down == '1' || down == ' ') && (left == '1'
			|| left == ' ') && (right == '1' || right == ' '))
		return (1);
	return (0);
}
