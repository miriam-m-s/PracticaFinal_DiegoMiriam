#ifndef __BARCAS_H__
#define __BARCAS_H__
#include"../SDL_Utils/GameObject.h"

//class SpaceClient;
class GameObject;
class Barcas:public GameObject{
public:
    Barcas(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer,spaceClient){

    }; //
    ~Barcas();
    
    
};
#endif /*__GAMEOBJECT_H__*/
