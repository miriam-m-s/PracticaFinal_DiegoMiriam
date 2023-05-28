#include "Enemy.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../../RedUtils/Message.h"
#include "../SDL_Utils/Environment.h"

Enemy::Enemy(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer, spaceClient){ //

}

void Enemy::update(float deltaTime){

}

void Enemy::setID(int id){
    myID = id;
}