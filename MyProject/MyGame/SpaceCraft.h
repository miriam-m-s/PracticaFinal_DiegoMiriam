#ifndef __SPACECRAFT_H__
#define __SPACECRAFT_H__
#include"../SDL_Utils/GameObject.h"
#include <vector>

class GameObject;

class SpaceCraft:public GameObject{
public:
    SpaceCraft(SDL_Renderer* renderer, SpaceClient *spaceClient); //
    ~SpaceCraft();
    
    virtual void handleInput(const SDL_Event &event);
    virtual void OnCollision(GameObject *other);

    void moveShip(int input);
    void setID(int id);
    void update(float deltaTime);
    void setIniPos(int posIniX_, int posIniY_);
    int getID();

private:
    int myID = 0;
    int posIniX, posIniY;
};
#endif
