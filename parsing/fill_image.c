/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:18:45 by abdo              #+#    #+#             */
/*   Updated: 2025/10/04 10:49:18 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_side(char *s)
{
	int	i;
	int	l;

	i = 0;
	l = ft_strlen(s);
	if (!s || !*s)
		return (0);
	while (s[i] == ' ')
		i++;
	if (s[i] != '1')
		return (0);
	if (s[l - 1] == '1' || s[l - 1] == ' ')
		return (1);
	return (0);
}

void	fill_img(char *str, char *path, t_player *player)
{
	int	l;

	l = ft_strlen(path);
	while (l > 0)
	{
		if (path[l] == '.')
			break ;
		l--;
	}
	if (ft_strncmp(path + l, ".xpm", 4))
	{
		free(path);
		printf("the image should use .xpm extension\n");
		exit(1);
	}
	if (*str == 'N')
		player->northimg = path;
	else if (*str == 'S')
		player->southimg = path;
	else if (*str == 'W')
		player->westimg = path;
	else
		player->eastimg = path;
}

int	open_fille(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	return (fd);
}

int	path_checker(char *s, t_player *player)
{
	int		i;
	int		start;
	char	*path;

	i = 3;
	start = 0;
	path = NULL;
	while (s[i] == ' ')
		i++;
	start = i;
	if (s[i] == '\0')
		return (0);
	while (s[i] && s[i] != ' ')
		i++;
	path = ft_substr(s, start, i - start);
	if (!open_fille(path))
	{
		free(path);
		return (0);
	}
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] != '\0')
		return (0);
	fill_img(s, path, player);
	return (1);
}
