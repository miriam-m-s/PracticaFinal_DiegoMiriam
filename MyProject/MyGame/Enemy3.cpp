#include "Enemy3.h"

#include<iostream>

#include "Cliente/SpaceClient.h"
#include "Bala.h"
#include "../SDL_Utils/Environment.h"

Enemy3::Enemy3(SDL_Renderer* renderer, SpaceClient *spaceClient):Enemy(renderer, spaceClient){ //

}

Enemy3::~Enemy3(){
    
}

void Enemy3::update(float deltaTime){

    timerForMove += deltaTime;

    if(timerForMove >= moveTimer){
        tr->Translate(tranlateX,0);
        timerForMove = 0.0f;
    }
}

void Enemy3::changeDirection(){
    tranlateX *= -1;
}

void Enemy3::shoot(){

    auto bullet=new Bala(environment().renderer(), spaceClient);
    bullet->setImage("Assets/Weapons.png", 24, 8, 8, 8);
    bullet->setScale(0.1, 0.1);
    bullet->setPosition(GetPositionX()+GetWidth()/2 - bullet->GetWidth()/2, GetPositionY() + GetHeight());
    bullet->setDirection(1);

    spaceClient->addGameObjectToScene(bullet);
    spaceClient->addBullet(bullet);
}

void Enemy3::OnCollision(GameObject *other){

}