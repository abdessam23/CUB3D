/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flor_rof.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:14:39 by abdo              #+#    #+#             */
/*   Updated: 2025/10/01 10:37:30 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


int ft_atoichecker(char **s,char *str, t_player *player)
{
	int i;
	i = 0;
	int n;
	while (s[i])
	{
		n = ft_atoi(s[i]);

		if (n < 0 || n > 255)
			return 0;
		if (*(str - 2) == 'F')
			player->floor[i] = n;
		else
			player->roof[i] = n;
		i++;
	}
	if (i != 3)
		return 0;
	return 1;
}
void ft_free(char **arr)
{
    int  i;
    
    i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
int check_range(char *s, t_player *player)
{
	int  i;
	int start;
	char **arr;
	char *range = NULL;
	i = 0;
	start = 0;
	while (s[i] && s[i] == ' ')
		i++;
	start = i;
	if (s[i] == '\0')
		return 0;
	while (s[i] && s[i] != ' ')
		i++;
	range = ft_substr(s,start, i - start);
	start = 0;

	while(range[start])
	{
		if (!ft_isdigit(range[start]) && range[start] != ',')
			return 0;
		start++;
	}
	arr = ft_split(range, ',');
	if (!ft_atoichecker(arr,s, player))
		return 0;
	while (s[i] && s[i] == ' ')
		i++;
	if(s[i] != '\0')
		return 0;
	free(range);
    ft_free(arr);
	return 1;
}
