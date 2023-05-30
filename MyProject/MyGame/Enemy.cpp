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

    for(auto enemy = actualExtremesOfEnemies1.begin(); enemy != actualExtremesOfEnemies1.end(); enemy++){
        
        if(i == 0){
            if((*enemy)->GetPositionX() <= 0){
                tranlateInY = true;
                auxiliarMove *= -1;
            }
        }

        else {
            if((*enemy)->GetPositionX() >= environment().width() - (*enemy)->GetWidth()){

                tranlateInY = true;
                auxiliarMove *= -1;
            }
        }
        
        i++;
   
    }

    if(tranlateInY){
        for(auto enemy = enemies1.begin(); enemy != enemies1.end(); enemy++){

            int x = (*enemy)->GetPositionX() + auxiliarMove;
            int y = (*enemy)->GetPositionY() + translateY;

            (*enemy)->tr->SetPosition(x,y);
            (*enemy)->changeDirection();
        }
    }

    timerForShoot += deltaTime;

    if(timerForShoot >= shootTimer){

        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, enemies1.size() - 1);
        int randomIndex = distribution(generator);
        enemies1[randomIndex]->shoot();
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
        break;

        case ENEMY3:
        break;

    }
}

void Enemy::addEnemyExtreme(Enemy *enemy, EnemyType enemyType){
    
    switch(enemyType){

        case ENEMY1:
            actualExtremesOfEnemies1.push_back(enemy);
        break;

        case ENEMY2:
        break;

        case ENEMY3:
        break;

    }
}