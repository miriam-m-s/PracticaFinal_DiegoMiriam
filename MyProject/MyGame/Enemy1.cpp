#include "Enemy1.h"

#include<iostream>

#include "Cliente/SpaceClient.h"
#include "Bala.h"
#include "../SDL_Utils/Environment.h"

Enemy1::Enemy1(SDL_Renderer* renderer, SpaceClient *spaceClient):Enemy(renderer, spaceClient){ //

}

Enemy1::~Enemy1(){
    
}

void Enemy1::update(float deltaTime){

    timerForMove += deltaTime;

    if(timerForMove >= moveTimer){
        tr->Translate(tranlateX,0);
        timerForMove = 0.0f;
    }
}

void Enemy1::setID(int id){
    myID = id;
}

void Enemy1::changeDirection(){
    tranlateX *= -1;
}

void Enemy1::shoot(){

    auto bullet=new Bala(environment().renderer(), spaceClient);
    bullet->setImage("Assets/Weapons.png", 16, 8, 8, 8);
    bullet->setScale(0.1, 0.1);
    bullet->setPosition(GetPositionX()+GetWidth()/2 - bullet->GetWidth()/2, GetPositionY() + GetHeight());
    bullet->setDirection(1);

    spaceClient->addGameObjectToScene(bullet);
    spaceClient->addBullet(bullet);
}