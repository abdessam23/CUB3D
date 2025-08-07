/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:13:00 by abdo              #+#    #+#             */
/*   Updated: 2025/08/07 11:13:22 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"

int check_arg(char *s)
{
    char *str;
    str = ft_strrchr(s,'.');
    if (strcmp(str, ".cub") == 0)
        return 1;
    return -1;
}
int ft_identif(int c)
{
    if (c == 'S' || c == 'W' || c == 'N' || c == 'E' ||
        c == 'F' || c == 'C')
        return 1;
    return 0;
}
int check_ident(char *s)
{
    int i;
    i = 0;
    if (!s)
        return 0;
    while (s[i] == ' ')
        i++;
    if (!ft_identif(s[i]))
        return 0;
    return 1;
}
char *read_line(char *s)
{
    char buf[10];
    int fd;
    int rbyt = 1;
    char *str = NULL;
    if (!s)
        return NULL;
    fd = open(s,O_RDONLY,640);
    if (fd == -1)
        return NULL;
    while (rbyt != 0)
    {
        rbyt = read(fd,buf, 10);
        if (rbyt  == 0)
            break;
        str = ft_strjoin(str, buf);
        ft_memset(buf,0,10);
    }
    close(fd);
    
    return str;
}
char **fill_map(char *s)
{
    char **p;
    char *str;
    if (!*s)
        return NULL;
 
    str = read_line(s); 
    p = ft_split(str, '\n');
    return p;
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
    if (!s || !*s)
        return 0;
    while (s[i] == ' ')
        i++;
    if (s[i] != '1')
        return 0;
    while (s[i])
    {
        if(s[i + 1] == '\0' && s[i] == '1')
            return 1;
        i++;
    }
    return 0;
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
void check_walls(char **map)
{
    char **str;
    str = map + 6;
    int i = 0;
    while (str[i] != NULL)
        i++;
    if (!checkup_down(str[0]) || !checkup_down(str[i - 1])  || !check_side(str))
        printf(" no wall");
    else
        printf("walls are ok");
        
}
int main(int argc, char **argv)
{
    int fd;
    char **map;
    int i;
    if (argc != 2)
        return 1;
    if (check_arg(argv[1]) == -1)
    {
        printf("Error\n");
        return 1;
    }
    map =fill_map(argv[1]);
    if (!map)
        return 1;
    for (i = 0; map[i] != NULL; i++)
    {
        if (i < 6)
        {
            if (!check_ident(map[i]))
            {
                printf("Error : the order does'nt corret!");
                return 1;
            }
        }
        printf("%s\n", map[i]);
    }
    check_walls(map);
    
    return 0;
}