#include "Enemy.h"
#include<iostream>
#include "Cliente/SpaceClient.h"
#include "../SDL_Utils/Environment.h"

Enemy::Enemy(SDL_Renderer* renderer, SpaceClient *spaceClient_):GameObject(renderer, spaceClient_), spaceClient(spaceClient_){ //

}

Enemy::~Enemy(){
    
}

void Enemy::update(float deltaTime){

    int i = 0;
    bool tranlateInY = false;

    timerForMove += deltaTime;

    if(timerForMove >= moveTimer){
        tr->Translate(tranlateX,0);
        timerForMove = 0.0f;
    }

    if(GetPositionX() <= 0 || GetPositionX() >= environment().width() - GetWidth()){
        tranlateX *= -1;
        auxiliarMove *= -1;
        tr->SetPosition(GetPositionX() + auxiliarMove,GetPositionY());
        tranlateInY = true;
    }

    if(tranlateInY){
        for(auto enemy = enemies1.begin(); enemy != enemies1.end(); enemy++){

            int x = (*enemy)->GetPositionX();
            int y = (*enemy)->GetPositionY() + translateY;

            (*enemy)->tr->SetPosition(x,y);
            (*enemy)->changeDirection();
        }
    }

    timerForShoot += deltaTime;

    if(timerForShoot >= shootTimer && myID == 0){

        // std::random_device rd;
        // std::mt19937 generator(rd());
        // std::uniform_int_distribution<int> distribution(0, enemies1.size() - 1);
        // int randomIndex = distribution(generator);

        // spaceClient->enemyHasToShoot(randomIndex, ENEMY1);

        // randomIndex = distribution(generator);
        // spaceClient->enemyHasToShoot(randomIndex, ENEMY2);

        timerForShoot = 0.0f;
    }

}

void Enemy::setID(int id){
    myID = id;
}

void Enemy::addEnemy(Enemy *enemy, EnemyType enemyType){
    
    switch(enemyType){

        case ENEMY1:
            enemies1.push_back(enemy);
        break;

        case ENEMY2:
            enemies2.push_back(enemy);
        break;

        case ENEMY3:
            enemies3.push_back(enemy);
        break;

    }
}

void Enemy::orderShoot(int enemyType, int enemySelected){
    switch(enemyType){

        case ENEMY1:
            enemies1[enemySelected]->shoot();
        break;

        case ENEMY2:
            enemies2[enemySelected]->shoot();
        break;

        case ENEMY3:
            enemies3[enemySelected]->shoot();
        break;

    }
}