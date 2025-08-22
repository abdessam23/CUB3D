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
    double stepX;
    double stepY;
    double wallp;
    int mapX = (int)player.playerX;
    int mapY = (int)player.playerY;
    int side = 0;
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
            if (raydiX < 0)
            {
                dsidX = (player.playerX - mapX) * dx;
                stepX = -1;
            }
            else
            {
                dsidX = (mapX + 1.0 - player.playerX) * dx;
                stepX = 1;
            }
            if (raydiY < 0)
            {
                dsidX = (player.playerY - mapY) * dy;
                stepX = -1;
            }
            else
            {
                dsidX = (mapY + 1.0 - player.playerY) * dy;
                stepX = 1;
            }
            while (!hit)
            {
                if (dsidX < dsidY)
                {
                    dsidX += dx;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    dsidY += dy;
                    mapY += stepY;
                    side = 1;
                }
                if (player.map[mapX][mapY] == '1') // we need map here!!
                    hit = 1;
            }
            if (side == 0)
                wallp = dsidX - dx;
            else
                wallp = dsidY - dy;
            
                
        }
    }
    

}