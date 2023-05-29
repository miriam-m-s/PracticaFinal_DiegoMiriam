#ifndef __SPACECRAFT_H__
#define __SPACECRAFT_H__
#include"../SDL_Utils/GameObject.h"

//class SpaceClient;

class SpaceCraft:public GameObject{
public:
    SpaceCraft(SDL_Renderer* renderer, SpaceClient *spaceClient); //
    
    virtual void handleInput(const SDL_Event &event);
    ~SpaceCraft();

    void moveShip(int input);
   
    void setID(int id);
    void update(float deltaTime);

private:
    int myID = 0;
    bool isShooting;
    float shootTimer = 0.0f;

};
#endif /*__GAMEOBJECT_H__*/
