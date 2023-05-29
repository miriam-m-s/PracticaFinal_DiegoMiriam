#include "SpaceCraft.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"
#include "../SDL_Utils/Environment.h"
SpaceCraft::SpaceCraft(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer, spaceClient),isShooting(false){ //

}
void SpaceCraft::handleInput(const SDL_Event &e){
    

    if (e.type == SDL_KEYDOWN ){

		int action;

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
                        if (shootTimer <= 0.0f) {
                            isShooting = true;
                            shootTimer = 4.0f; // Establecer el temporizador de disparo en 0.5 segundos
                           
                            std::cout << "Shooting" << std::endl;
                        }
                       
                break;
            }
     

        spaceClient->sendAction(action, myID);
	}
}

void SpaceCraft::moveShip(int input){

    switch (input)
    {
    case Message::Input::LEFT:
        tr->SetPosition(tr->GetPositionX()-5,tr->GetPositionY());
        break;
    case Message::Input::RIGHT://tecla derecha
        tr->SetPosition(tr->GetPositionX()+5,tr->GetPositionY());
      break;
    }


}
void SpaceCraft::update(float deltaTime){

    if (isShooting) {

        // Actualizar la lógica de los disparos
        shootTimer -= deltaTime; 

        if (shootTimer <= 0.0) {
            isShooting = false; // Reiniciar el estado de disparo cuando el temporizador alcanza cero
        }
    }
    if(tr->GetPositionX()<-GetWidth()){
         tr->SetPosition(environment().width(),tr->GetPositionY());
    }
    else if(tr->GetPositionX()>environment().width()){
        tr->SetPosition(-GetWidth(),tr->GetPositionY());
    }
}
void SpaceCraft::setID(int id){
    myID = id;
}