#include "SpaceCraft.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"
#include "../SDL_Utils/Environment.h"
#include "Lava.h"
#include "Enemy.h"

SpaceCraft::SpaceCraft(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer, spaceClient), myID(0){ //
    myID = 0;
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
                case  SDLK_w:
                    action = 3;
                    spaceClient->sendAction(action, myID);
                break;
                case SDLK_s:
                    action=0;
                    spaceClient->sendAction(action, myID);
                break;
            }
        }
    
    
}

void SpaceCraft::moveShip(int input){

    switch (input)
    {
    case Message::Input::LEFT:
        tr->SetPosition(tr->GetPositionX()-5,tr->GetPositionY());
        tr->setRotation(270.0f);
        break;
    case Message::Input::RIGHT:
        tr->SetPosition(tr->GetPositionX()+5,tr->GetPositionY());
        tr->setRotation(90.0f);
      break;
    case Message::Input::DOWN:
        tr->SetPosition(tr->GetPositionX(),tr->GetPositionY() + 5);
        tr->setRotation(180.0f);
        break;
    case Message::Input::UP:
        tr->SetPosition(tr->GetPositionX(),tr->GetPositionY() - 5);
        tr->setRotation(0.0f);
      break;
    }


}

void SpaceCraft:: OnCollision(GameObject *other){

    Lava* lava = dynamic_cast<Lava*>(other);
    Enemy *enemy = dynamic_cast<Enemy*>(other);

    if(lava!= nullptr || enemy != nullptr){
        setPosition(posIniX, posIniY);
    }
}

void SpaceCraft::update(float deltaTime){

    if(tr->GetPositionX() <= 0){
        tr->SetPosition(0,tr->GetPositionY());
    }
    if(tr->GetPositionX()>=environment().width()-GetWidth()){
        tr->SetPosition(environment().width() - GetWidth(),tr->GetPositionY());
    }
    if(tr->GetPositionY()<=0){
        tr->SetPosition(tr->GetPositionX(),0);
    }
    if(tr->GetPositionY()>=environment().height()-GetHeight()){
        tr->SetPosition(tr->GetPositionX(),environment().height()-GetHeight());
    }
    
}

void SpaceCraft::setID(int id){
    myID = id;
}

int SpaceCraft::getID(){
    return myID;
}

void SpaceCraft::setIniPos(int posIniX_, int posIniY_){
    posIniX = posIniX_;
    posIniY = posIniY_;
}