#include <stdlib.h>
#include <math.h>

#include "sdl-draw.h"

int draw_polygon(SDL_Renderer *renderer, const struct polygon *p)
{
    if (renderer == NULL)
        return -1;

    if (p == NULL)
        return -1;

    SDL_FPoint *points = (SDL_FPoint *)p->points;

    SDL_RenderDrawLinesF(renderer, points, p->nsides);
    SDL_RenderDrawLineF(renderer,
            points[0].x, points[0].y,
            points[p->nsides - 1].x, points[p->nsides - 1].y);

    return 0;
}

static int fpolycmp(const void *a, const void *b)
{
    return *(float *)a - *(float *)b;
}

int draw_polygon_filled(SDL_Renderer *renderer, const struct polygon *p)
{
    if (renderer == NULL)
        return -1;

    if (p == NULL)
        return -1;

    struct point *points = (struct point *)p->points;

    float max_y = points[0].y;
    float min_y = points[0].y;

    for (int i = 0; i < p->nsides; i ++)
    {
        max_y = points[i].y > max_y ? points[i].y : max_y;
        min_y = points[i].y < min_y ? points[i].y : min_y;
    }

    int nint;
    float *nodes_x = (float *)malloc(sizeof(float) * p->nsides);

    for (int y = min_y; y <= max_y; y++)
    {
        nint = 0;

        //  Build a list of nodes.
        int ind1;
        int ind2;
        for (int i = 0; i < p->nsides; i++)
        {
            float x1;
            float y1;
            float x2;
            float y2;

            // get current point at i == 0
            if (i == 0) {
                ind1 = p->nsides - 1;
                ind2 = 0;
            } else {
                ind1 = i - 1;
                ind2 = i;
            }

            y1 = points[ind1].y;
            y2 = points[ind2].y;
            if (y1 < y2) {
                x1 = points[ind1].x;
                x2 = points[ind2].x;
            } else if (y1 > y2) {
                y2 = points[ind1].y;
                y1 = points[ind2].y;
                x2 = points[ind1].x;
                x1 = points[ind2].x;
            } else {
                continue;
            }
            if ( ((y >= y1) && (y < y2)) || ((y == max_y) && (y > y1) && (y <= y2)) )
            {
                nodes_x[nint++] = (y - y1) * (x2 - x1) / (y2 - y1) + x1;
            }

        }

        qsort(nodes_x, nint, sizeof(float), fpolycmp);

        if (nint % 2 == 0)
            for (int k = 0; k < nint; k += 2)
                SDL_RenderDrawLineF(renderer, nodes_x[k], y, nodes_x[k + 1], y);
    }

    free(nodes_x);

    return 0;
}
