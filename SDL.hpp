#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define delay(x) SDL_Delay(x)
class SDL
{
private:
    int width;
    int height;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *fonte;
    SDL_Texture *texture;

public:
    SDL(int w, int h, int fonts);
    ~SDL();

    void clear();
    void Draw();
    void SetPixel(int x, int y, int r, int g, int b, int a = 255);
    bool PediuPraSair();
    void Print(int x, int y, std::string texto, SDL_Color cor = {255, 250, 255});
    void DrawArray(const void *px);
    int textH();
};
