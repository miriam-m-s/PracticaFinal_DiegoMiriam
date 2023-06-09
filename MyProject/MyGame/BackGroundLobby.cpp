#include "BackGroundLobby.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"
#include "../SDL_Utils/Text.h"

BackGroundLobby::BackGroundLobby(SDL_Renderer* renderer, SpaceClient *spaceClient, Text *text_):GameObject(renderer, spaceClient),spaceClient_(spaceClient),text(text_){ //

}

void BackGroundLobby::recieveMesage(int state){
    if(state=Message::MessageType::READY){
        changeState=true;
        text->ChangeText("PRESS SPACE TO PLAY");
    }
}

void BackGroundLobby::handleInput(const SDL_Event &e){
    

    if (e.type == SDL_KEYDOWN&&changeState ){

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