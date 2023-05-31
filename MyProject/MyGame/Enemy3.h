#ifndef __ENEMY3_H__
#define __ENEMY3_H__
#include"Enemy.h"

class Enemy3:public Enemy{
public:
    Enemy3(SDL_Renderer* renderer, SpaceClient *spaceClient); //    
    ~Enemy3();

    virtual void update(float deltaTime);

    virtual void changeDirection();

    virtual void shoot();

    virtual void OnCollision(GameObject *other);

private:

    float tranlateX=10;

};
#endif /*__GAMEOBJECT_H__*/