#include "SDL.hpp"

//--------------------------------------------------------------------------------
//------------- ROTULO -----------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

void rotulo::setTexto(string txt)
{
    texto = txt;
    atualizarTextura();
    atualizarRect();
};
void rotulo::setPos(int x, int y)
{
    Message_rect.x = x;
    Message_rect.y = y;
    atualizarRect();
};
void rotulo::atualizarTextura()
{
    surface =
        TTF_RenderText_Shaded(fonte, texto.c_str(), corFrente == nullptr ? BRANCO : *corFrente, corFundo == 0 ? TRANSPARENTE : *corFundo);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
};
void rotulo::atualizarRect()
{
    TTF_SizeText(fonte, texto.c_str(), &w, &h);
    Message_rect.w = w;
    Message_rect.h = h;
};
void rotulo::draw()
{
    SDL_RenderCopy(renderer, texture, NULL, &Message_rect);
};
