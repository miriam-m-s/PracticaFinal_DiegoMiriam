#include "Bala.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"

Bala::Bala(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer, spaceClient),velocidad(5){ //

}
void Bala::update(float deltaTime){
       float desplazamiento = velocidad * deltaTime;

        tr->SetPosition(tr->GetPositionX(),tr->GetPositionY()-desplazamiento);
}
void Bala::setID(int id){
    myID = id;
}