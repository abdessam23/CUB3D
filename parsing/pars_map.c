/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:58:53 by abdo              #+#    #+#             */
/*   Updated: 2025/08/09 18:46:17 by abdo             ###   ########.fr       */
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

// int check_map_recursive(char *str, int count)
// {
//     if (count == 6)
//     {
//         while (*str && ft_whitespace(*str))
//             str++;
//         if (*str == '1')
//             return 1;
//         else
//             return 0;
//     }
//     while (*str && ft_whitespace(*str))
//         str++;
//     if (*str == '\0' || !ft_identif(*str))
//         return 0;
//     while (*str && *str != '\n')
//         str++;
//     return check_map_recursive(str, count + 1);
// }

// int check_map(char *s)
// {
//    char *str = read_line(s);
//     if (!str ||*str == '\0' )
//         return 0;
//     return check_map_recursive(str, 0);
// }

// int check_map(char *s)
// {
//     char *str;
//     int count = 0;
//     int line;
//     if (!*s)
//         return 0;
    
//     str = read_line(s);
//     if (*str)
//     {
//        while (*str && ft_whitespace(*str))
//             str++;
        
//         if (ft_identif(*str))
//         {
//             while (*str && *str != '\n')
//                 str++;
//             while (*str && ft_whitespace(*str)) str++; 
//             if (ft_identif(*str))
//             {
//                 while (*str && *str != '\n')
//                     str++;
//                 while (*str && ft_whitespace(*str)) str++;                           
//                 if (ft_identif(*str))
//                 {
//                     while (*str && *str != '\n')
//                         str++;
//                     while (*str && ft_whitespace(*str)) str++;
//                     if (ft_identif(*str))
//                     {
//                         while (*str && *str != '\n')
//                             str++;
//                         while (*str && ft_whitespace(*str)) str++;
//                         if (ft_identif(*str))
//                         {
//                             while (*str && *str != '\n')
//                                 str++;
//                             while (*str && ft_whitespace(*str)) str++;
//                             if (ft_identif(*str))
//                             {
//                                 while (*str && *str != '\n')
//                                 str++;
//                                 while (*str && ft_whitespace(*str)) str++;
//                                 printf("f : %c f1:%c\n",*str,*(str+1));
//                                 if(*str == '1')
//                                     return 1;
//                                 else
//                                     return 0;
//                             }
//                             else
//                                 return 0;
//                         }
//                         else
//                                 return 0;
//                     }
//                     else
//                                 return 0;   
//                 }
//                 else
//                                 return 0; 
//             }
            
//         }
//         else
//             return 0;
//     }
//     return 0;
//}

int is_valid(int c)
{
    if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return 1;
    return 0;
}
int check_map(char *s)
{
    int count = 0;
    char *str = read_line(s);

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
            if(*str == '1')
            {
                
                while (*str && (ft_whitespace(*str) || is_valid(*str)))
                    str++;
                if (*str == '\0')
                    return 1;
                return 0;
            }
        }
    }
    return (0);
}
int main(int argc, char **argv)
{
    int fd;
    int map;
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