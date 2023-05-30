#include "Bala.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"
#include "../SDL_Utils/Environment.h"

Bala::Bala(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer, spaceClient),velocidad(200){ //

}
Bala::~Bala(){
    
}
void Bala::update(float deltaTime){
    float desplazamiento = velocidad * deltaTime;
    
    tr->SetPosition(tr->GetPositionX(),tr->GetPositionY() + direction*desplazamiento);
    if((tr->GetPositionY()-desplazamiento)>=environment().height()|| (tr->GetPositionY()-desplazamiento)<0){
        enabled_ = false;
    }

}
void Bala::setID(int id){
    myID = id;
}

void Bala::setDirection(int dir){
    direction = dir;
}