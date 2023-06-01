#ifndef __VICTORY_H__
#define __VICTORY_H__
#include"../SDL_Utils/GameObject.h"

//class SpaceClient;
class GameObject;
class Victory:public GameObject{
public:
    Victory(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer,spaceClient){};
    ~Victory();
    
    
};
#endif /*__GAMEOBJECT_H__*/
