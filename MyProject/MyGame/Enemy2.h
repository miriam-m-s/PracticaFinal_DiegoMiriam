#ifndef __ENEMY2_H__
#define __ENEMY2_H__
#include"Enemy.h"

class Enemy2:public Enemy{
public:
    Enemy2(SDL_Renderer* renderer, SpaceClient *spaceClient); //    
    ~Enemy2();

    virtual void update(float deltaTime);

    virtual void changeDirection();

    virtual void shoot();

    virtual void OnCollision(GameObject *other);

private:

    float tranlateX=10;

};
#endif /*__GAMEOBJECT_H__*/