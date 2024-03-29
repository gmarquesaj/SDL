

#include "SDL.hpp"

void SDL:: processarEventos(){

    while (SDL_PollEvent(&event))
    {
        pediuPraSair= (event.type == SDL_QUIT);
	if(event.type == SDL_KEYDOWN && onKeyBoardPress!= NULL)
	{
		const Uint8* teclas = SDL_GetKeyboardState(NULL);
		onKeyBoardPress(teclas);
	}
            
    }

   
};
SDL::SDL(int w, int h, int fonts, string titulo)
{
    width = w;
    height = h;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
    SDL_SetWindowTitle(window, titulo.c_str());
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    TTF_Init();
    fonte = TTF_OpenFont("/usr/share/fonts/truetype/freefont/FreeMono.ttf", fonts);
    if (!fonte)
        cout << "Falha ao abrir fonte\n";
    texture = SDL_CreateTexture(
        renderer,
        format,
        SDL_TEXTUREACCESS_STREAMING,
        width, height);
    surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, format);
}
void SDL::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}
void SDL::draw()
{
    SDL_RenderPresent(renderer);
}
SDL::~SDL()
{
    cout << "SDL_DestroyTexture(texture);\n";
	
    SDL_DestroyTexture(texture);
    cout << "SSDL_FreeSurface(surface);\n";
    SDL_FreeSurface(surface);
    cout << "SSDL_DestroyRenderer(renderer);\n";
    SDL_DestroyRenderer(renderer);
    cout << "SSDL_DestroyWindow(window);\n";
    SDL_DestroyWindow(window);
    cout << "SSDL_Quit();\n";
    SDL_Quit();
}
void SDL::setPixel(int x, int y, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}
void SDL::print(int x, int y, string texto, SDL_Color cor)
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
void SDL::drawArray(const void *px)
{
    SDL_UpdateTexture(
        texture,
        NULL,
        px,
        width * NumCanais);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}
void SDL::drawArrayLockTexture(const void *px, const int pxSize)
{

    unsigned char *lockedPixels = nullptr;
    int pitch = 0;
    SDL_LockTexture(
        texture,
        NULL,
        reinterpret_cast<void **>(&lockedPixels),
        &pitch);
    memcpy(lockedPixels, px, pxSize);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_UnlockTexture(texture);
}
int SDL::textH()
{

    return TTF_FontHeight(fonte);
};

void SDL::printScreenBMP(const char *caminho)
{
    SDL_RenderReadPixels(renderer, NULL, format, surface->pixels, surface->pitch);
    SDL_SaveBMP(surface, caminho);
}
void SDL::retangulo(int rx, int ry, int rw, int rh, int r, int g, int b)
{
    SDL_Rect ret = {rx, rx, rw, rh};
    if (r > -1 and g > -1 and b > -1)
        SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &ret);
}
SDL_Texture *SDL::criarImagem(const char *caminho)
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
void SDL::desenhaImagem(SDL_Texture *img, SDL_Rect *origem, SDL_Rect *saida)
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
void SDL:: setarFonte(string caminho,int fonts)
{
    fonte = TTF_OpenFont(caminho.c_str(), fonts);
    if (!fonte)
 	    cout << "Falha ao abrir fonte\n";

};
int SDL:: circulo( int x, int y, int radius,int r, int g, int b)
{
    int offsetx, offsety, d;
    int status;
    offsetx = 0;
    offsety = radius;
    d = radius -1;
    status = 0;

    SDL_SetRenderDrawColor(renderer,r,g,b, 255);
    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                     x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                     x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                     x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                     x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        }
        else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        }
        else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}
