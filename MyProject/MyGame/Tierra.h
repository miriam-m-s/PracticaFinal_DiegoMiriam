#ifndef __TIERRA_H__
#define __TIERRA_H__
#include"../SDL_Utils/GameObject.h"

//class SpaceClient;
class GameObject;
class Tierra:public GameObject{
public:
    Tierra(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer,spaceClient){};
    ~Tierra();
    
    
};
#endif /*__GAMEOBJECT_H__*/
