

#include "SDL.hpp"

SDL::SDL(int w, int h, int fonts, string titulo)
{
    width = w;
    height = h;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN /* | SDL_WINDOW_FULLSCREEN_DESKTOP */, &window, &renderer);
    SDL_SetWindowTitle(window, titulo.c_str());
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    TTF_Init();
    fonte = TTF_OpenFont("/usr/share/fonts/TTF/Comic.TTF", fonts);
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
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void SDL::setPixel(int x, int y, int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawPoint(renderer, x, y);
}
bool SDL::pediuPraSair()
{

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return true;
    }

    return false;
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