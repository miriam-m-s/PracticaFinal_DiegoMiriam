#include <SDL2/SDL.h>
#include"GameObject.h"
int main() {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL no pudo inicializarse. Error: %s\n", SDL_GetError());
        return 1;
    }

    // Crear una ventana
    SDL_Window* ventana = SDL_CreateWindow("Mi ventana SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (ventana == NULL) {
        printf("No se pudo crear la ventana. Error: %s\n", SDL_GetError());
        return 1;
    }
    // Obtener el renderer de la ventana
    SDL_Renderer* renderer = SDL_CreateRenderer(ventana, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("No se pudo crear el renderer. Error: %s\n", SDL_GetError());
        return 1;
    }

    // Establecer el color de fondo del renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    GameObject ship(renderer);
    ship.setImage("../Assets/naves.png", 8, 0, 8, 8);

    // Esperar hasta que el usuario cierre la ventana
    bool salir = false;
    SDL_Event evento;
    while (!salir) {
        // Borrar el contenido del renderer con el color de fondo
        SDL_RenderClear(renderer);
        while (SDL_PollEvent(&evento) != 0) {
            if (evento.type == SDL_QUIT) {
                salir = true;
            }
            
        }
        ship.Render();
        SDL_RenderPresent(renderer);
    }
  
    SDL_DestroyWindow(ventana);
    SDL_Quit();

    return 0;
}
