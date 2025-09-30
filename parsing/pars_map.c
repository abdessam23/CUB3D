/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:58:53 by abdo              #+#    #+#             */
/*   Updated: 2025/09/29 18:19:00 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"


int check_arg(char *s)
{
	char *str;
	str = ft_strrchr(s,'.');
	if (strcmp(str, ".cub") == 0) //should use our strcmp
		return 1;
	return -1;
}

char *read_line(char *s)
{
	char buf[11];   // +1 for null terminator
	int fd;
	int rbyt;
	char *str = NULL;

	if (!s)
		return NULL;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		return NULL;

	while ((rbyt = read(fd, buf, 10)) > 0)
	{
		buf[rbyt] = '\0';               // null-terminate
		str = ft_strjoin(str, buf);     // join existing + new chunk
	}

	close(fd);
	return str;
}

/*char *read_line(char *s)*/
/*{*/
/*    char buf[10];*/
/*    int fd;*/
/*    int rbyt = 1;*/
/*    char *str = NULL;*/
/*    if (!s)*/
/*        return NULL;*/
/*    fd = open(s,O_RDONLY,640);*/
/*    if (fd == -1)*/
/*        return NULL;*/
/*    while (rbyt != 0)*/
/*    {*/
/*        rbyt = read(fd,buf, 10);*/
/*        if (rbyt  == 0)*/
/*            break;*/
/*        str = ft_strjoin(str, buf);*/
/*        ft_memset(buf,0,10);*/
/*    }*/
/*    close(fd);*/
/*    return str;*/
/*}*/

int ft_whitespace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return 1;
	return 0;
}
int ft_identif(int c)
{
	if (c == 'S' || c == 'W' || c == 'N' || c == 'E' ||
		c == 'F' || c == 'C')
		return 1;
	return 0;
}
int iswhitespace(char *s)
{
	while (*s)
	{
		if(*s != ' ')
			return 0;
		s++;
	}
	return 1;
}

int is_valid(int c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return 1;
	return 0;
}
int check_inside_map(char *str)
{
	int i;
	i = 0;
	while (*str)
	{
		while (is_valid(*str) && *str != '\n')
			str++;
		if(*str != '\0' && *str != '\n' && !is_valid(*str))
			return 0;
		str++;
		if (*str == '\n')
		{
			while (*str && ft_whitespace(*str))
				str++;
			if (*str == '\0')
				return 1;
			return 0;
		}

	}
	return 1;
}
int check_map(char *s)
{
	int count = 0;
	char *str = ft_strdup(s);
	while(*str)
	{
		while (*str && ft_whitespace(*str))
			str++;
		if (*str == '\0' || !ft_identif(*str))
			return 0;

		while (*str && *str != '\n')
			str++;
		while (*str && ft_whitespace(*str))
			str++;
		count++;
		if (count == 6)
		{
			if(*str == '1' && check_inside_map(str))
				return 1;
			return 0;
		}
	}
	return (0);
}
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
int ft_side(char *s)
{
	int i =0;
	int len = ft_strlen(s);
	if (!s || !*s)
		return 0;
	while (s[i] == ' ')
		i++;
	if (s[i] != '1')
		return 0;
	/*while (s[i])*/
	/*{*/
	/*    if(s[i + 1] != ' ' && s[i] != '1')*/
	/*        return 1;*/
	/*    i++;*/
	/*}*/
	if (s[len - 1] == '1' || s[len - 1] == ' ')
		return 1;
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
int find_one(char **map)
{
	int i;
	int j;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] == ' ')
			j++;
		if(map[i][j] == '1')
			return i;
		i++;
	}
	return 0;

}

int ft_direction(int c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return 1;
	return 0;
}

int duplicatID(char **str, t_player *player)
{
	int i;
	int x;
	int y;
	int j;
	int count;
	int flag;
	flag = 0;
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
				player->playerX = (float)j; //position of player
				player->playerY = (float)i;  //position of player
				player->direction = str[i][j]; // derection of player
			}        
		}
	}
	if (count > 1)
		return 0;
	return 1;
}
char	**create_test_map(void)
{
	char **map = malloc(sizeof(char*) * 10);

	map[0] = ft_strdup("111111111111111111111111111111");
	map[1] = ft_strdup("100001000000000000000001000001");
	map[2] = ft_strdup("100000000100100000000000000001");
	map[3] = ft_strdup("101000011110111111011110000001");
	map[4] = ft_strdup("100000010000000001000000000001");
	map[5] = ft_strdup("100000010000000001111100000001");
	map[6] = ft_strdup("100001000000000000000000000001");
	map[7] = ft_strdup("100000000000N00001000000001001");
	map[8] = ft_strdup("100000111100000001000000000001");
	map[9] = ft_strdup("111111111111111111111111111111");

	return (map);
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
	player->map = str; // map 
	return 1;         
}

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
		free(path); //free all
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
int identif_checker(char *s1,char *s2,t_player *player)
{
	int i;

	i = 0;
	while (*s1 == ' ')
		s1++;

	if (*s1 == *s2)
	{
		if (ft_strncmp(s1, s2, 3))
			return 0;
		if (!path_checker(s1,player))
			return 0;
	}
	return 1;
}
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
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return 1;
}
int check_singlid(char *s,t_player *player)
{
	while (*s && *s == ' ')
		s++;
	if(*s == 'F')
	{
		if(ft_strncmp(s,"F ", 2))
			return 0;
		if (!check_range(s+2, player))
			return 0;
	}
	if(*s == 'C')
	{
		if(ft_strncmp(s,"C ", 2))
			return 0;
		if (!check_range(s+2, player))
			return 0;
	}
	return 1;
}
char *ft_idchar(char c)
{
	if (c == 'S')
		return (ft_strdup("SO "));
	if (c == 'N')
		return (ft_strdup("NO "));
	if (c == 'W')
		return (ft_strdup("WE "));
	if (c == 'E')
		return (ft_strdup("EA "));
	return NULL;  
}

int ft_valid_id(char *str,t_player *player)
{
	int i;
	char *identif = NULL;
	i = 0;

	while (str[i] && str[i] == ' ')
		i++;
	//should check null terminator here
	if (ft_identif(str[i]))
	{

		if (str[i] == 'S' || str[i] == 'W' || str[i] == 'N' || str[i] == 'E')
		{
			identif = ft_idchar(str[i]);
			if (!identif_checker(str, identif,player))
			{
				free(identif);
				return 0;
			}

		}
		if (str[i] == 'F' || str[i] == 'C')
		{
			if(!check_singlid(str, player))
				return 0;
		}
	}
	if (identif)
		free(identif);
	return 1;
}
int pars_fun(int argc, char **argv, t_player *player)
{
	char *str;
	char  **map;

	if (argc != 2)
		return 1;
	if (check_arg(argv[1]) == -1)
	{
		printf("Error\n");
		return 1;
	}
	str = read_line(argv[1]);
	if (!check_map(str))
	{
		printf("Error: unexcepted in map\n");
		return 1;
	}
	map = ft_split(str, '\n');
	if (!map)
		return 1;
	for (int i = 0; map[i] != NULL; i++)
	{
		if (!ft_valid_id(map[i],player))
		{
			printf("Error: identifier");
			return 1;
		}
	}
	if (!check_in_map(map, player))
	{
		printf("issue inside map");
		return 1;
	}
	// printf("valid map!\n");

	// for(int i = 0; player->map[i] ;i++)
	// {
	//     printf("%s\n", player->map[i]);
	// }
	// printf("player cordonne: %f,%f\n",player->playerX,player->playerY);
	// printf("Noth img : %s\n",player->northimg);
	// printf("South img : %s\n",player->southimg);
	// printf("Eest img : %s\n",player->eastimg);
	// printf("West img : %s\n",player->westimg);
	// printf("Direction  : %c\n",player->direction);
	// printf("Floor: %d,%d,%d\n",player->floor[0],player->floor[1],player->floor[2]);
	//  printf("roof: %d,%d,%d\n",player->roof[0],player->roof[1],player->roof[2]);
	return 0;
}
