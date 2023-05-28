#ifndef __ENEMY_H__
#define __ENEMY_H__
#include"../SDL_Utils/GameObject.h"

class Enemy:public GameObject{
public:
    Enemy(SDL_Renderer* renderer, SpaceClient *spaceClient); //    
    ~Enemy();
    void setID(int id);
    void update(float deltaTime);

private:
    float velocidad=5;
    int myID = 0;
   

};
#endif /*__GAMEOBJECT_H__*/