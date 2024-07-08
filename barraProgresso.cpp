#include "SDL.hpp"

void barraProgresso::draw()
{
    float p = max == 0 or pos <= 0 ? 0 : pos > max ? 1
                                                   : pos / max;
    int w1, w2;
    SDL_Rect rects, rect, rect1, rect2;
    if (slider)
    {
        w1 = (w - sw) * p;
        w2 = (w)-w1;
        rects = {x + w1, y, sw, h};
        rect = {x, y, w, h};
        rect1 = {x, y, w1, h};
        rect2 = {x + w1, y, w2, h};
    }
    else
    {
        w1 = w * p;
        w2 = w - w1;
        rects = {x + w1, y, sw, h};
        rect = {x, y, w, h};
        rect1 = {x, y, w1, h};
        rect2 = {x + w1, y, w2, h};
    }

    SDL_SetRenderDrawColor(renderer, 100, 255, 100, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect1);

    SDL_SetRenderDrawColor(renderer, 150, 50, 200, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect2);

    if (slider)
    {
        bool naArea = mouse->mouseNaArea(rect);

        if (naArea)
        {
            if (mouse->esq)
            {
                int m = mouse->mouseX;
                m = m < x + sw ? x + sw : m > w + x - sw ? w + x - sw
                                                         : m;
                pos = map_from_to(m, x + sw, w + x - sw, 0, max);
                printf("P = %f\n", pos);
                w1 = (w - sw) * p;
                rects = {x + w1, y, sw, h};
                // pos=
            }
        }
        if (naArea)
            SDL_SetRenderDrawColor(renderer, 5, 50, 5, SDL_ALPHA_OPAQUE);
        else
            SDL_SetRenderDrawColor(renderer, 255, 50, 5, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rects);
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);
}
