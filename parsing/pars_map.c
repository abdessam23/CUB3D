/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:58:53 by abdo              #+#    #+#             */
/*   Updated: 2025/08/09 16:12:04 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
int check_map(char *s)
{
    char *str;
    int count = 0;
    int line;
    if (!*s)
        return 0;
    
    str = read_line(s);
    if (*str)
    {
       while (*str && ft_whitespace(*str))
            str++;
        
        if (ft_identif(*str))
        {
            while (*str && *str != '\n')
                str++;
            while (*str && ft_whitespace(*str)) str++; 
            if (ft_identif(*str))
            {
                while (*str && *str != '\n')
                    str++;
                while (*str && ft_whitespace(*str)) str++;                           
                if (ft_identif(*str))
                {
                    while (*str && *str != '\n')
                        str++;
                    while (*str && ft_whitespace(*str)) str++;
                    if (ft_identif(*str))
                    {
                        while (*str && *str != '\n')
                            str++;
                        while (*str && ft_whitespace(*str)) str++;
                        if (ft_identif(*str))
                        {
                            while (*str && *str != '\n')
                                str++;
                            while (*str && ft_whitespace(*str)) str++;
                            if (ft_identif(*str))
                            {
                                while (*str && *str != '\n')
                                str++;
                                while (*str && ft_whitespace(*str)) str++;
                                printf("f : %c f1:%c\n",*str,*(str+1));
                                if(*str == '1')
                                    return 1;
                            }
                            else
                                return 0;
                        }
                        else
                                return 0;
                    }
                    else
                                return 0;   
                }
                else
                                return 0; 
            }
            
        }
        else
            return 0;
    }
    return 0;
}

int main(int argc, char **argv)
{
    int fd;
    int map;
    int i;
    int c;
    if (argc != 2)
        return 1;
    // if (check_arg(argv[1]) == -1)
    // {
    //     printf("Error\n");
    //     return 1;
    // }
    map =check_map(argv[1]);
    // if (!map)
    //     return 1;
    // for (i = 0; map[i] != NULL; i++)
    // {
    //     if (check_ident(map[i]))
    //     {
    //         if (!check_ident(map[i]))
    //         {
    //             // printf("Error : the order does'nt correct!");
    //             return 1;
    //         }
    //     }
    //     // printf("%s\n",map[i]);
    // }
    // if (!check_walls(map))
    // {
    //     printf("walls issue");
    //     return 1;
    // }
    if (!map)
        printf("there are unxcepted thing map\n");
    else
        printf("ok!\n");
    return 0;
}