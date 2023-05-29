#include "SpaceCraft.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"
#include "../SDL_Utils/Text.h"

BackGroundLobby::BackGroundLobby(SDL_Renderer* renderer, SpaceClient *spaceClient, Text *text):GameObject(renderer, spaceClient){ //

}

void BackGroundLobby::BackGroundLobby(const SDL_Event &e){
    

    if (e.type == SDL_KEYDOWN ){

		int action;

        switch (e.key.keysym.sym)
        {
            case SDLK_SPACE: 
                    action=1;              
            break;
        }
     

        spaceClient->sendAction(action, myID);
	}
}