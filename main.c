/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo <abdo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 13:13:00 by abdo              #+#    #+#             */
/*   Updated: 2025/09/29 17:07:25 by abdo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cube.h"

int main(int arc, char **argv)
{
    t_player player;
    if (pars_fun(arc,argv, &player))
    {
        printf ("pars\n");
        return 1;
    }
    if (init_cube(&player))
     {
        printf ("ray\n");
        return 1;
    }
    return 0;
}