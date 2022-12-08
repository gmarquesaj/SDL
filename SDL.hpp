#pragma once

/*
######################################################
##   CRIADO POR GILSON MARQUES ALVES JUNIOR         ##
##   EM 3/12/2022 - Pirapora MG Brasil              ##
##   CONTATOS                                       ##
##   55038984177956 gmarquesaj@gmail.com            ##
##   Facilita o uso do SDL para desenhar Texturas   ##
##       (compilar usando  -lSDL2 -lSDL2_ttf)       ##
######################################################
*/

#include <cstring>
#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#define delay(x) SDL_Delay(x)
#define NumCanais 4
#define format SDL_PIXELFORMAT_RGB888
#define imagemP SDL_Texture *
using std::cout;
using std::memcpy;
using std::string;
using std::to_string;
using std::vector;
class SDL
{
private:
public:
    int width;
    int height;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *fonte;
    SDL_Texture *texture;
    SDL_Surface *surface;
    SDL(int w, int h, int fonts, string titulo = "SDL");
    ~SDL();

    void clear();
    void draw();
    void setPixel(int x, int y, int r, int g, int b, int a = 255);
    bool pediuPraSair();
    void print(int x, int y, std::string texto, SDL_Color cor = {255, 250, 255});
    void drawArray(const void *px);
    void drawArrayLockTexture(const void *px, const int pxSize);
    void printScreenBMP(const char *caminho);
    int textH();
    void retangulo(int rx, int ry, int rw, int rh, int r, int g, int b);
    SDL_Texture * criarImagem( const char *caminho);
    void desenhaImagem(SDL_Texture *img, SDL_Rect *origem = NULL, SDL_Rect *saida = NULL);
};
