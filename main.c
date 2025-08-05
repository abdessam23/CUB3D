/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:13:00 by abdo              #+#    #+#             */
/*   Updated: 2025/08/05 17:08:26 by abdo             ###   ########.fr       */
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
    str = strrchr(s,'.');
    if (strcmp(str, ".cub") == 0)
        return 1;
    return -1;
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
int main(int argc, char **argv)
{
    int fd;
    char **map;
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
    for (int i = 0; map[i] != NULL; i++)
    {
        printf("%s\n", map[i]);
    }
    
    return 0;
}