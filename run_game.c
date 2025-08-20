#include "cub3d.h"
int *direction(char c)
{
    int *p = malloc(sizeof(int) * 2);
    if (c == 'N' || c == 'S')
    {
        p[0] = 0;
        if (c == 'N')
            p[1] = -1;
        else
            p[1] = 1;
        return p;
    }
    if (c == 'E' || c == 'W')
    {
        p[1] = 0;
        if (c == 'W')
            p[0] = -1;
        else
            p[0] = 1;
        return p;
    }
    return 0;
}


void run_game(t_player player)
{
    float cameraX;
    float planeX;
    float planeY;
    float raydiX;
    float raydiY;
    double dx;
    double dy;
    double dsidX;
    double dsidY;
    int hit = 0;
    int *p;
    int dirX;
    int dirY;
    planeX = 0;
    planeY  = 0.66;
    p = direction(player.direction);
    dirX = p[0];
    dirY = p[1];
    free(p);
    while (!hit)
    {
        for (int i = 0; i < width - 1; i++)
        {
            cameraX = 2 * i/width - 1;
            raydiX = dirX + planeX * cameraX;
            raydiY = dirY + planeY * cameraX;
            dx = sqrt(1 + raydiY * raydiY / (raydiX * raydiX));
            dy = sqrt(1 + raydiX * raydiX / (raydiY * raydiY));


        }
    }
    

}