#ifndef __BALACRAFT_H__
#define __BALACRAFT_H__
#include"../SDL_Utils/GameObject.h"

//class SpaceClient;

class Bala:public GameObject{
public:
    Bala(SDL_Renderer* renderer, SpaceClient *spaceClient); //    
    ~Bala();
    void setID(int id);
    void update(float deltaTime);

private:
    float velocidad=5;
    int myID = 0;
   

};
#endif /*__GAMEOBJECT_H__*/
