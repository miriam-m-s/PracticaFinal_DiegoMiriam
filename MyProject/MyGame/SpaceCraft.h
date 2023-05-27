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
    void shoot();
    void setID(int id);

private:
    SDL_Scancode left_, right_;
    int myID = 0;
    bool isShooting;

};
#endif /*__GAMEOBJECT_H__*/