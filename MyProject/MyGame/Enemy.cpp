#include "Enemy.h"
#include "Lava.h"
#include "Cliente/SpaceClient.h"

void Enemy::update(float deltaTime){
    if(myID == 0) {

        int flip_;

        if(flip == SDL_FLIP_HORIZONTAL) flip_ = 0;
        else flip_ = 1;

        spaceClient->moveEnemies(tr->GetPositionX() + direction*velocity, index, flip_);

    }
}

void Enemy:: OnCollision(GameObject *other){
    Lava* lava = dynamic_cast<Lava*>(other);
    if(lava!=nullptr) {
        direction *= -1;
        tr->SetPosition(GetPositionX() + direction*velocityAuxiliar, GetPositionY());
        if(direction > 0) flip = SDL_FLIP_HORIZONTAL;
        else flip = SDL_FLIP_NONE;
    }
}

void Enemy::setID(int id){
    flip = SDL_FLIP_HORIZONTAL;
    myID = id;
}

void Enemy::setIndex(int index_){
    index = index_;
}

void Enemy::move(int x, int flip_){
    tr->SetPosition(x, GetPositionY());

    if(flip_ == 0){
        flip = SDL_FLIP_HORIZONTAL;
    }
    else flip = SDL_FLIP_NONE;
}