/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:03:11 by abdo              #+#    #+#             */
/*   Updated: 2025/10/01 11:30:04 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../cube.h"

int checkup_down(char *s)
{
	int i = 0;

	while (s[i])
	{
		if (s[i] != ' ' &&  s[i] != '1')
			return 0;
		i++;
	}
	return 1; 
}


int check_side(char **str)
{
	int i = 1;
	int  j;
	while (str[i])
	{
		if (!ft_side(str[i]))
			return 0;
		i++;
	}
	return 1;
}

int ft_spaces(char **str, int i, int j)
{
    if(str[i][j] == ' ')
    {
        if(!check_spaces(str,i, j))
        return 0;
    }
    return 1;       
}
int duplicatID(char **str, t_player *player)
{
    int i;
    int x;
    int y;
    int j;
    int count;

    i = 0;
    count  = 0;
    while (str[++i])
    {
        j = 0;
        while (str[i][++j])
        {
            if(ft_direction(str[i][j]))
            {
                count++;
                player->playerX = (double)j; //position of player
                player->playerY = (double)i;  //position of player
                player->direction = str[i][j]; // derection of player
            }
            if(count > 0 || !ft_spaces(str,i,j))
                return 0;
        }
    }
    return 1;
}


int check_in_map(char **map,t_player *player)
{
	char **str;
	int n = 0;
	n = find_one(map);
	if(n == 0)
		return 0;
	str = map + n;
	int i = 0;
	if (!str || !*str)
		return 0;

	while (str[i] != NULL)
		i++;
	if (i > 0 && (!checkup_down(str[0]) || !checkup_down(str[i - 1])  || !check_side(str)))
		return 0;
	if (!duplicatID(str,player))
		return 0;
	player->map = str;  
	return 1; 
}
