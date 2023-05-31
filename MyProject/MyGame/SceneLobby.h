#ifndef __SCENELOBBY_H__
#define __SCENELOBBY_H__
#include"../SDL_Utils/Scene.h"

class SpaceClient;

class SceneLobby: public Scene {

public:
    SceneLobby(SDL_Renderer* renderer, SpaceClient *spaceClient); //
    ~SceneLobby(){};
    virtual void handleCollision() {};
private:

};
#endif /*__SCENE1_H__*/