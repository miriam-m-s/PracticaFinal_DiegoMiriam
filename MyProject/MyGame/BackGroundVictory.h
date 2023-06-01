#ifndef __BACKGROUNDVICTORY_H__
#define __BACKGROUNDVICTORY_H__
#include"../SDL_Utils/GameObject.h"

class Text;
class Message;

class BackGroundVictory:public GameObject{
public:
    BackGroundVictory(SDL_Renderer* renderer, SpaceClient *spaceClient); //
    
    virtual void handleInput(const SDL_Event &event);
    ~BackGroundVictory();

    virtual void OnCollision(GameObject *other){};

private:
    bool changeState=false;
    SpaceClient *spaceClient_;
};
#endif /*__GAMEOBJECT_H__*/