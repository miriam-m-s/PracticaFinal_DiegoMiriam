#ifndef __ENEMY1_H__
#define __ENEMY1_H__
#include"Enemy.h"

class Enemy1:public Enemy{
public:
    Enemy1(SDL_Renderer* renderer, SpaceClient *spaceClient); //    
    ~Enemy1();

    virtual void update(float deltaTime);

    virtual void changeDirection();

    virtual void shoot();

    virtual void OnCollision(GameObject *other);

private:

    float tranlateX=10;

};
#endif /*__GAMEOBJECT_H__*/