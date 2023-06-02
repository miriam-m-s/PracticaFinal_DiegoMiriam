#ifndef __TIERRA_H__
#define __TIERRA_H__
#include"../SDL_Utils/GameObject.h"

class Tierra:public GameObject{
public:
    Tierra(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer,spaceClient){};
    ~Tierra();
        virtual void OnCollision(GameObject *other) {};
    
};
#endif
