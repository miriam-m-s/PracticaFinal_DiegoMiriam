#include <SDL2/SDL.h>
#include"SDL_Utils/GameObject.h"
#include"SDL_Utils/Scene.h"
#include"MyGame/Scene1.h"
#include "SDL_Utils/Environment.h"
#include<queue>

int main() {

    Environment::init("Miri", 640, 480);

    SDL_Renderer* renderer = environment().renderer();

    // Establecer el color de fondo del renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    std::queue<Scene*> scenes_;
    scenes_.push(new Scene1(renderer));
    

    // Esperar hasta que el usuario cierre la ventana
    bool salir = false;
    SDL_Event event;
    while (!salir) {
        
       

		Uint32 startTime = environment().currRealTime();
		while (SDL_PollEvent(&event))
		{
			// Salir del server
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				salir=true;
				continue;
			}

			
            scenes_.front()->handleEvent(event);
		}

		
		scenes_.front()->update();


		environment().clearRenderer({0, 30, 160});

		scenes_.front()->render();
     

		environment().presentRenderer();

		Uint32 frameTime = environment().currRealTime() - startTime;
		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
    }
  
    // SDL_DestroyWindow(ventana);
    // SDL_Quit();

    return 0;
}
