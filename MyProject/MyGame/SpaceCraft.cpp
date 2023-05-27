#include "SpaceCraft.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"

SpaceCraft::SpaceCraft(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer, spaceClient),isShooting(false){ //

}
void SpaceCraft::handleInput(const SDL_Event &e){
    

    if (e.type == SDL_KEYDOWN ){

		int action;
        int shipMoved;
            switch (e.key.keysym.sym)
            {
                case SDLK_a: 
                        action=1;              
                break;

                case SDLK_d:   
                        action=2; 
                break;
                case  SDLK_SPACE:  
                        action=0;                  
                        shoot();
                 break;          
                break;
            }
     

        spaceClient->sendAction(action, myID);
	}
}

void SpaceCraft::moveShip(int input){

    switch (input)
    {
    case Message::Input::SPACE://tecla space

        break;
    case Message::Input::LEFT:
        tr->SetPosition(tr->GetPositionX()-5,tr->GetPositionY());
        break;
    case Message::Input::RIGHT://tecla derecha
        tr->SetPosition(tr->GetPositionX()+5,tr->GetPositionY());
      break;
    }


}

void SpaceCraft::setID(int id){
    myID = id;
}
void SpaceCraft::shoot(){

}