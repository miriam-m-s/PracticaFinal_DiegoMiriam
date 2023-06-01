#ifndef __LAVA_H__
#define __LAVA_H__
#include"../SDL_Utils/GameObject.h"

//class SpaceClient;
class GameObject;
class Lava:public GameObject{
public:
    Lava(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer,spaceClient){

    }; //
    ~Lava();
    
    
};
#endif /*__GAMEOBJECT_H__*/
