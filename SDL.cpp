

#include "SDL.hpp"
SDL_Color BRANCO = {255, 255, 255, 255};
SDL_Color PRETO = {1, 1, 1, 255};
SDL_Color VERMELHO = {255, 1, 1, 255};
SDL_Color VERDE = {1, 255, 1, 255};
SDL_Color AZUL = {1, 1, 255, 255};
SDL_Color AMARELO = {255, 255, 1, 255};
SDL_Color TRANSPARENTE = {255, 255, 255, 1};
SDL_Color TRANSPARENTE2 = {0, 0, 0, 1};


float fInvLerp(int x1, int x2, int p)
{
	if (x1 == x2)
	{
		// cout << "VALORES IGUAIS\n";
		return 1.0;
	}
	if (p > x2 or p < x1)
	{
		cout << "ERRO NO INVER LERP\n";
		return 1.0;
	}
	float t = ((float)(p - x1) / (float)(x2 - x1));
	t = t < 0.0 ? 0.0 : t > 1.0 ? 1.0
								: t;
	return t;
}
float fLerp(float v0, float v1, float t)
{
	if (t > 1 or t < 0)
	{
		cout << "FORA DO LIMITE\n";
	}
	t = t < 0 ? 0 : t > 1 ? 1
						  : t;
	return (1.0f - t) * v0 + t * v1;
};
float map_from_to(float x, float a, float b, float c, float d)
{
	return (x - a) / (b - a) * (d - c) + c;
}


/// MOUSE//
void mouseInfo::atualizar()
{
	mouseState = SDL_GetMouseState(&mouseX, &mouseY);
	esq = (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT));
	dir = (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT));
	meio = (mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE));
}

bool mouseInfo::mouseNaArea(SDL_Rect posDim)
{
     return (mouseX >= posDim.x && mouseX <= posDim.x + posDim.w &&
            mouseY >= posDim.y && mouseY <= posDim.y + posDim.h);
}

///
bool janela::mouseJustPress()
{

    bool c = mouse.esq;
    if (c == false)
    {
        justPress = false;
        return false;
    }
    if (c and justPress == true)
    {
        return false;
    }
    justPress = true;
    cout << "ACABOU DE APERTAR\n";
    return true;
};
void janela::processarEventos()
{
    while (SDL_PollEvent(&event))
    {
        pediuPraSair = (event.type == SDL_QUIT);
        if (event.type == SDL_KEYDOWN && onKeyBoardPress != NULL)
        {
            SDL_Scancode scancode = event.key.keysym.scancode;
            std::cout << "Scancode: " << scancode << std::endl;
            const Uint8 *teclas = SDL_GetKeyboardState(NULL);
            onKeyBoardPress(teclas);
            continue;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
           // cout << "SDL_MOUSEBUTTONDOWN\n";
            continue;
        }
        if (event.type == SDL_MOUSEBUTTONUP)
        {
           // cout << "SDL_MOUSEBUTTONUP\n";
            continue;
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            int x = event.motion.x;
                int y = event.motion.y;
                int xrel = event.motion.xrel;
                int yrel = event.motion.yrel;
                mouse.mouseXR=xrel;
                mouse.mouseYR=yrel;
              //  std::cout << "Mouse moved to (" << x << ", " << y << ") with relative movement (" << xrel << ", " << yrel << ")\n";
            continue;
        }
        if (event.type == SDL_MOUSEWHEEL)
        {
           // cout << "SDL_MOUSEWHEEL\n";
            continue;
        }
    }

    tempoNovo = agora;
    tempoAtual = tempoNovo - tempoVelho;
    int64_t nanos = tempoAtual.count();
    fps = 1000000000.0 / (nanos);
    if (limitar)
    {
        Uint64 espera = fmax(0, (33000000L - nanos) / 1000000);
        //    printf("fps %f tempo %lu  espera %lu\n",fps,nanos,espera);
        SDL_Delay(espera);
        tempoNovo = agora;
        tempoAtual = tempoNovo - tempoVelho;
        int64_t nanos = tempoAtual.count();
        fps = 1000000000.0 / (nanos);
    }
    tempoVelho = tempoNovo;
};

janela::janela(int w, int h, int fonts, string titulo)
{
    width = w;
    height = h;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, SDL_RENDERER_ACCELERATED | SDL_WINDOW_OPENGL, &window, &renderer);
    SDL_SetWindowTitle(window, titulo.c_str());
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    TTF_Init();
    fonte = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf", fonts);
    if (!fonte)
        cout << "Falha ao abrir fonte\n";
    cout << "criada interna\n";
    surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 24, format);
    tempoVelho = agora;
}

void janela::clear()
{
    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255);
    SDL_RenderClear(renderer);
}

void janela::draw()
{
    SDL_RenderPresent(renderer);
}

janela::~janela()
{

    cout << "SDL_FreeSurface(surface);\n";
    SDL_FreeSurface(surface);
    cout << "SDL_DestroyRenderer(renderer);\n";
    SDL_DestroyRenderer(renderer);
    cout << "SSDL_DestroyWindow(window);\n";
    SDL_DestroyWindow(window);
    cout << "SDL_Quit();\n";
    SDL_Quit();
}

void janela::setPixel(int x, int y, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}

void janela::print(int x, int y, string texto, SDL_Color *frente, SDL_Color *fundo)
{
    // SDL_Surface *surfaceMessage = TTF_RenderText_Solid(fonte, texto.c_str(), White);

    SDL_Surface *surfaceMessage =
        TTF_RenderText_Shaded(fonte, texto.c_str(), frente == nullptr ? BRANCO : *frente, fundo == 0 ? TRANSPARENTE : *fundo);
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

int janela::textH()
{
    return TTF_FontHeight(fonte);
};

void janela::printScreenBMP(const char *caminho)
{
    SDL_RenderReadPixels(renderer, NULL, format, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface, caminho);
}

void janela::retangulo(int rx, int ry, int rw, int rh, int r, int g, int b)
{
    SDL_Rect ret = {rx, ry, rw, rh};
    if (r > -1 and g > -1 and b > -1)
        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

    SDL_RenderDrawRect(renderer, &ret);
}
void janela::retanguloF(int rx, int ry, int rw, int rh, int r, int g, int b)
{
    SDL_Rect ret = {rx, ry, rw, rh};
    if (r > -1 and g > -1 and b > -1)
        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);

    SDL_RenderFillRect(renderer, &ret);
}
SDL_Texture *janela::criarImagem(const char *caminho)
{
    SDL_Surface *si = SDL_LoadBMP(caminho);

    SDL_Texture *img;
    if (si == NULL)
    {
        cout << "ERRO AO LER A IMAGEM \"" << SDL_GetError() << "\" \n";
        exit(1);
    }
    img = SDL_CreateTextureFromSurface(renderer, si);
    if (img == NULL)
    {
        cout << "ERRO AO CRIAR A IMAGEM \"" << SDL_GetError() << "\" \n";
        exit(1);
    }
    SDL_FreeSurface(si);
    return img;
};

void janela::desenhaImagem(SDL_Texture *img, SDL_Rect *origem, SDL_Rect *saida)
{
    if (img == NULL)
    {
        cout << "ERRO IMAGEM nula \"" << SDL_GetError() << "\" \n";
        exit(1);
    }
    int erro = SDL_RenderCopy(renderer, img, origem, saida);
    if (erro != 0)
    {
        cout << " ERRO AO DESENHAR IMAGEM \"" << erro << "\" : \"" << SDL_GetError() << "\" \n";
    };
};

void janela::setarFonte(string caminho, int fonts)
{
    fonte = TTF_OpenFont(caminho.c_str(), fonts);
    if (!fonte)
        cout << "Falha ao abrir fonte\n";
};

int janela::circulo(int x, int y, int radius, int r, int g, int b)
{
    int offsetx, offsety, d;
    int status;
    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    while (offsety >= offsetx)
    {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0)
        {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx)
        {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        }
        else if (d < 2 * (radius - offsety))
        {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else
        {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}
