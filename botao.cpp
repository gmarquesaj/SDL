#include "SDL.hpp"

//--------------------------------------------------------------------------------
//------------- BOTAO  -----------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

botao::botao(int x, int y, int w, int h, string titulo, SDL_Renderer *renderer, TTF_Font *fonte)
    : renderer(renderer), posDim({.x = x, .y = y, .w = w, .h = h}), titulo(titulo), fonte(fonte)
{
    SDL_Surface *surfaceMessage =
        TTF_RenderText_Shaded(fonte, titulo.c_str(), {255, 255, 255, 255}, {250, 250, 250, 1});
    textureBranco = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    surfaceMessage =
        TTF_RenderText_Shaded(fonte, titulo.c_str(), {0, 0, 0, 255}, {250, 250, 250, 1});
    texturePreto = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);

    int textw = 0;
    int texth = 0;
    TTF_SizeText(fonte, titulo.c_str(), &textw, &texth);
    int textx = (w - textw) / 2;
    int texty = (h - texth) / 2;

    Message_rect.x = x + textx;
    Message_rect.y = y + texty;
    Message_rect.w = textw;
    Message_rect.h = texth;
};
void botao::draw()
{
    int mouseX, mouseY;
    Uint32 mouse = SDL_GetMouseState(&mouseX, &mouseY);
    bool esq = (mouse & SDL_BUTTON(SDL_BUTTON_LEFT));
    bool dir = (mouse & SDL_BUTTON(SDL_BUTTON_RIGHT));

    mouseEmCima = (mouseX >= posDim.x && mouseX <= posDim.x + posDim.w &&
                   mouseY >= posDim.y && mouseY <= posDim.y + posDim.h);

    if (mouseEmCima == true)
    {
        if (esq == true)
        {
            clicado = true;
            liberado = false;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(renderer, 50, 50, 200, 255);
            if (clicado == true)
            {
                liberado = true;
                clicado = false;
            }
            else
            {
            }
        }
    }
    else
    {
        liberado = false;
        clicado = false;
        SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    }

    SDL_RenderFillRect(renderer, &posDim);

    if (mouseEmCima)
        SDL_RenderCopy(renderer, textureBranco, NULL, &Message_rect);
    else
        SDL_RenderCopy(renderer, texturePreto, NULL, &Message_rect);

    if (liberado && aoPressionar)
    {
        aoPressionar();
        liberado = false;
        clicado = false;
    }
};