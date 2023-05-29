#include "BackGroundLobby.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"
#include "../SDL_Utils/Text.h"

BackGroundLobby::BackGroundLobby(SDL_Renderer* renderer, SpaceClient *spaceClient, Text *text_):GameObject(renderer, spaceClient),spaceClient_(spaceClient),text(text){ //

}
void BackGroundLobby:: recieveMesage(int state){
    if(state=Message::MessageType::WAITING){
        changeState=true;
       // text->ChangeText("PRESS SPACE TO PLAY");
    }
}

void BackGroundLobby::handleInput(const SDL_Event &e){
    

    if (e.type == SDL_KEYDOWN&&changeState ){

		int action;

        switch (e.key.keysym.sym)
        {
            case SDLK_SPACE: 
                    action=Message::MessageType::READY; 
                    spaceClient->sendMessage( action);             
            break;
        }
     

        
	}
}