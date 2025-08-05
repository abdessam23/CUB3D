/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:13:00 by abdo              #+#    #+#             */
/*   Updated: 2025/08/05 15:13:08 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

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
    char buf[100];
    int fd;
    int rbyt;
    
    fd = open(s,O_RDONLY,640);
    while ()
    {
        /* code */
    }
    
    
    
}
char **fill_map(char *s)
{
  
    char **p;
    char *str;
    int i = 0;
    char buf[100];
    while (*s && *s != '\n')
        i++;
    p = malloc(sizeof(char*) * (i + 1));
    str = read_line(s);
    
    
    
}
int main(int argc, char **argv)
{
    int fd;
    char **map;
    if (argc != 2)
        return 1;
    if (check_arg(argv[1]) == -1)
        return 1;
    map =fill_map(argv[1]);
    return 0;
}