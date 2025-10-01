/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:18:45 by abdo              #+#    #+#             */
/*   Updated: 2025/10/01 10:20:26 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube.h"



void fill_img(char *str,char *path,t_player *player)
{
	int l;
	l = ft_strlen(path);
	while (l > 0)
	{
		if (path[l] == '.')
			break;
		l--;
	}
	if (ft_strncmp(path+l,".xpm",4))
	{
		free(path);
		printf("the image should use .xpm extension\n");
		exit(1);
	}
	if (*str == 'N')
		player->northimg = path;
	else if(*str == 'S')
		player->southimg = path;
	else if(*str == 'W')
		player->westimg = path;
	else
		player->eastimg = path;
}
int path_checker(char *s, t_player *player)
{
	int i = 3;
	int start = 0;
	char *path = NULL;
	int fd;
	while (s[i] == ' ')
		i++;
	start = i;
	if (s[i] == '\0')
		return 0;
	while (s[i] && s[i] != ' ')
		i++;
	path = ft_substr(s,start, i - start);
	fd = open(path,O_RDONLY);
	if (fd == -1)
	{
		free(path);
		return 0;
	}
	while (s[i] && s[i] == ' ')
		i++;
	if (s[i] != '\0')
		return 0;
	fill_img(s,path,player);
	return 1;
}
