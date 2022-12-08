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
    int width;
    int height;
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *fonte;
    SDL_Texture *texture;
    SDL_Surface *surface;

public:
    SDL(int w, int h, int fonts, string titulo = "SDL");
    ~SDL();
    // Limpar a tela(preenche a tela com a cor de fundo)
    void clear();
    // Atualizar a tela
    void draw();
    // Desenha um unico pixel
    void setPixel(int x, int y, int r, int g, int b, int a = 255);
    // Retorna verdadeiro se o usuario tentou fechar a janela
    bool pediuPraSair();
    // Desenhar texto na tela
    void print(int x, int y, std::string texto, SDL_Color cor = {255, 250, 255});
    // Desenhar uma lista de pixels
    void drawArray(const void *px);
    // Desenhar uma lista de pixels usando "LOCK TEXTURE"
    void drawArrayLockTexture(const void *px, const int pxSize);
    // Salva o conteudo atual da tela para um arquivo BMP
    void printScreenBMP(const char *caminho);
    // Retorna a altura em pixels da fonte atual
    int textH();
    // Desenha um Retangulo
    void retangulo(int rx, int ry, int rw, int rh, int r, int g, int b);
    // Cria uma textura a partir de um arquivo BMP
    SDL_Texture *criarImagem(const char *caminho);
    // Desenha textura na posição e dimensoes especificadas
    void desenhaImagem(SDL_Texture *img, SDL_Rect *origem = NULL, SDL_Rect *saida = NULL);
};
