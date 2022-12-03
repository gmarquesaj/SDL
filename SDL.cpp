
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "SDL.hpp"

SDL::SDL(int w, int h, int fonts)
{
    width = w;
    height = h;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    TTF_Init();
    fonte = TTF_OpenFont("/usr/share/fonts/TTF/Comic.TTF", fonts);
    if (!fonte)
        std::cout << "Couldn't find/init open ttf font." << std::endl;
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGB888,
        SDL_TEXTUREACCESS_STREAMING,
        width, height);
}
void SDL::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}
void SDL::Draw()
{
    SDL_RenderPresent(renderer);
}
SDL::~SDL()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void SDL::SetPixel(int x, int y, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}
bool SDL::PediuPraSair()
{

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return true;
    }

    return false;
}
void SDL::Print(int x, int y, std::string texto, SDL_Color cor)
{
    // SDL_Surface *surfaceMessage = TTF_RenderText_Solid(fonte, texto.c_str(), White);
    SDL_Surface *surfaceMessage =
        TTF_RenderText_Shaded(fonte, texto.c_str(), cor, {0, 0, 0, 100});
    // now you can convert it into a texture
    SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    int w = 0;
    int h = 0;
    TTF_SizeText(fonte, texto.c_str(), &w, &h);
    SDL_Rect Message_rect;
    Message_rect.x = x;
    Message_rect.y = y;
    Message_rect.w = w;
    Message_rect.h = h;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}
void SDL::DrawArray(const void *px)
{
    SDL_UpdateTexture(
        texture,
        NULL,
        px,
        width * 4);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}
int SDL::textH()
{

    return TTF_FontHeight(fonte);
};
