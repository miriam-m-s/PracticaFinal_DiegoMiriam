#ifndef __VICTORY_H__
#define __VICTORY_H__
#include"../SDL_Utils/GameObject.h"

class Victory:public GameObject{
public:
    Victory(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer,spaceClient){};
    ~Victory();

    virtual void OnCollision(GameObject *other);

private:

    bool winner = false;
    
};
#endif