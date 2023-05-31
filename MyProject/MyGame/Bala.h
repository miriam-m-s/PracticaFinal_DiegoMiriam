#ifndef __BALACRAFT_H__
#define __BALACRAFT_H__
#include"../SDL_Utils/GameObject.h"

class SpaceCraft;
class Enemy;

class Bala:public GameObject{
public:
    Bala(SDL_Renderer* renderer, SpaceClient *spaceClient); //    
    ~Bala();

    virtual void update(float deltaTime);

    void Render();

    virtual void OnCollision(GameObject *other);

    void setID(int id);
    void setDirection(int dir);
    void setFromPlayer(bool fromPlayer_);
    bool isFromPlayer();

private:

    float velocidad=5;
    int direction = -1;
    int myID = 0;
    bool fromPlayer = false;
   

};
#endif /*__GAMEOBJECT_H__*/
