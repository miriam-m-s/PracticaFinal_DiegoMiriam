#ifndef __BACKGROUNDLOBBY_H__
#define __BACKGROUNDLOBBY_H__
#include"../SDL_Utils/GameObject.h"

class Text;
class Message;

class BackGroundLobby:public GameObject{
public:
    BackGroundLobby(SDL_Renderer* renderer, SpaceClient *spaceClient, Text *text_); //
    
    virtual void handleInput(const SDL_Event &event);
    ~BackGroundLobby();
    void recieveMesage(int state);

    virtual void OnCollision(GameObject *other){};

private:
     bool changeState=false;
    Text *text;
    SpaceClient *spaceClient_;
};
#endif /*__GAMEOBJECT_H__*/