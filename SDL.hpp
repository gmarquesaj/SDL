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
#include <chrono>
using timepoint = std::chrono::system_clock::time_point;
#define agora std::chrono::system_clock::now()
#define delay(x) SDL_Delay(x)
#define NumCanais 3
#define format SDL_PIXELFORMAT_RGB24
#define imagemP SDL_Texture *
using std::cout;
using std::memcpy;
using std::string;
using std::to_string;
using std::vector;

extern SDL_Color BRANCO;
extern SDL_Color PRETO;
extern SDL_Color VERMELHO;
extern SDL_Color VERDE;
extern SDL_Color AZUL;
extern SDL_Color AMARELO;
extern SDL_Color TRANSPARENTE;
extern SDL_Color TRANSPARENTE2;

class imagem
{
public:
	SDL_Texture *texture;
	SDL_Renderer *renderer;
	vector<unsigned char> pixels;
	SDL_Rect origem;
	SDL_Rect saida;
	int w, h, x, y;
	float escala;
	imagem(SDL_Renderer *renderer, int w, int h, int x, int y, float escala = 1.0);
	void draw();
	void updateTxt();
	void setPxl(int x, int y, SDL_Color *cor);
};
class rotulo
{
public:
	TTF_Font *fonte;
	SDL_Surface *surface;
	SDL_Texture *texture;
	SDL_Color *corFrente;
	SDL_Color *corFundo;
	SDL_Rect Message_rect;
	SDL_Renderer *renderer;

	string texto;
	int w = 0;
	int h = 0;
	void setTexto(string txt);
	void setPos(int x, int y);
	void draw();
	void atualizarTextura();
	void atualizarRect();
	rotulo(SDL_Renderer *renderer, TTF_Font *fonte, SDL_Color *corFrente, SDL_Color *corFundo, string txt, int x, int y) : renderer(renderer), fonte(fonte), corFrente(corFrente), corFundo(corFundo)
	{
		texto = txt;
		atualizarTextura();
		setPos(x, y);
	};
	~rotulo()
	{
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
};
class botao
{
public:
	SDL_Texture *textureBranco;
	SDL_Texture *texturePreto;
	TTF_Font *fonte;
	string titulo;
	SDL_Rect posDim;
	void (*aoPressionar)() = NULL;
	SDL_Renderer *renderer;
	void draw();
	botao(int x, int y, int w, int h, string titulo, SDL_Renderer *renderer, TTF_Font *fonte);
	bool mouseEmCima = false;
	bool clicado = false;
	bool liberado = false;
	SDL_Rect Message_rect;
};

class janela
{

public:
	int width;
	int height;
	SDL_Event event;
	SDL_Renderer *renderer;
	SDL_Window *window;
	TTF_Font *fonte;
	SDL_Surface *surface;
	bool limitar = false;
	timepoint tempoVelho;
	timepoint tempoNovo;
	std::chrono::nanoseconds tempoAtual;
	double fps;
	void (*onKeyBoardPress)(const Uint8 *teclas) = NULL;
	janela(int w, int h, int fonts, string titulo = "SDL");
	~janela();
	// Limpar a tela(preenche a tela com a cor de fundo)
	void clear();
	// Atualizar a tela
	void draw();
	// Desenha um unico pixel
	void setPixel(int x, int y, int r, int g, int b, int a = 255);
	// Retorna verdadeiro se o usuario tentou fechar a janela
	bool pediuPraSair = false;
	// Desenhar texto na tela
	void print(int x, int y, std::string texto, SDL_Color *frente = nullptr, SDL_Color *fundo = nullptr);

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
	// Definir a fonte pelo caminho
	void setarFonte(string caminho, int fonts);
	// Desenha um circulo completo
	int circulo(int x, int y, int radius, int r = 255, int g = 255, int b = 255);
	void processarEventos();
};
