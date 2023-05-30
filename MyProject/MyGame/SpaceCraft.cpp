#include "SpaceCraft.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"
#include "../SDL_Utils/Environment.h"
SpaceCraft::SpaceCraft(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer, spaceClient),isShooting(false), myID(0){ //
    
    myID = 0;
    for(int i=0;i<3;i++){

        auto hearts = new GameObject(renderer, spaceClient);
        hearts->setImage("Assets/SpaceShooterAssetPack_Miscellaneous.png", 16, 0, 8, 8);
        hearts->setScale(0.25f,0.25f);
        hearts_.push_back(hearts);
    }
}
void SpaceCraft::handleInput(const SDL_Event &e){
    
    if(spaceClient->getId()==myID)
        if (e.type == SDL_KEYDOWN ){

            int action;

            switch (e.key.keysym.sym)
            {
                case SDLK_a: 
                    action=1;   
                    spaceClient->sendAction(action, myID);           
                break;

                case SDLK_d:   
                    action=2; 
                    spaceClient->sendAction(action, myID);
                break;
                case  SDLK_SPACE:  
                    action=0;                 
                    if (shootTimer <= 0.0f) {
                        isShooting = true;
                        shootTimer = 0.5f; // Establecer el temporizador de disparo en 0.5 segundos
                        
                        spaceClient->sendAction(action, myID);
                        std::cout << "Shooting" << std::endl;
                    }
                break;
            }
        }
    
    
}
 void SpaceCraft:: Render(){
       GameObject::Render();
     for(int i=0;i<hearts_.size();i++){
         hearts_[i]->Render();
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
 void SpaceCraft:: OnCollision(GameObject *other){
 
    delete hearts_.back();
    hearts_.pop_back();
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
    int spaceBtwHearts=5;
    int posx=environment().width()-(3*hearts_[0]->GetWidth()+spaceBtwHearts*3);
    if(myID==0)posx=0;
    for(int i=0;i<hearts_.size();i++){
        hearts_[i]->setPosition(posx,5);
        posx+=hearts_[i]->GetWidth()+spaceBtwHearts;
       
    }
 
}