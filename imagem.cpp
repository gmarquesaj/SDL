#include "SDL.hpp"
//--------------------------------------------------------------------------------
//------------- IMAGEM -----------------------------------------------------------
//--------------------------------------------------------------------------------
//--------------------------------------------------------------------------------

imagem::imagem(SDL_Renderer *renderer, int w, int h, int x, int y, float escala) : renderer(renderer), w(w), h(h), x(x), y(y), escala(escala)
{
    if (renderer == NULL)
    {
        cout << "ponteiro nulo\n";
    }
    texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_STREAMING, w, h);

    pixels.resize(w * h * 3, 255);
    origem = {.x = 0, .y = 0, .w = w, .h = h};
    saida = {.x = x, .y = y, .w = int(w * escala), .h = int(h * escala)};
    updateTxt();
}

void imagem::draw()
{

    int erro = SDL_RenderCopy(renderer, texture, &origem, &saida);
    if (erro != 0)
    {
        cout << " ERRO AO DESENHAR IMAGEM \"" << erro << "\" : \"" << SDL_GetError() << "\" \n";
    };
};

void imagem::updateTxt()
{
    SDL_UpdateTexture(texture, 0, pixels.data(), w * NumCanais);
};
void imagem::setPxl(int x, int y, SDL_Color *cor)
{
    int pos = (y * w * NumCanais) + (x * NumCanais);
    pixels[pos + 0] = cor->r;
    pixels[pos + 1] = cor->g;
    pixels[pos + 2] = cor->b;
};