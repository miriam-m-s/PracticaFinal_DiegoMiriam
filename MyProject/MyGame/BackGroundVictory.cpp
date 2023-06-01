#include "BackGroundVictory.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"
#include "../SDL_Utils/Text.h"

BackGroundVictory::BackGroundVictory(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer, spaceClient),spaceClient_(spaceClient){ //

}

void BackGroundVictory::handleInput(const SDL_Event &e){
    

    if (e.type == SDL_KEYDOWN){

		int action;

        switch (e.key.keysym.sym)
        {
            case SDLK_SPACE: 
                    action=5; 
                    spaceClient->sendMessage( action);             
            break;
        }
     

        
	}
}