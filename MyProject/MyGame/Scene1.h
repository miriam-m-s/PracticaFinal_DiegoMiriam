#ifndef __SCENE1_H__
#define __SCENE1_H__
#include"../SDL_Utils/Scene.h"

class SpaceClient;

class Scene1: public Scene {
public:
    Scene1(SDL_Renderer* renderer, SpaceClient *spaceClient_); //
    ~Scene1(){};
    virtual void handleCollision();
private:
    bool checkCollision(GameObject *obj1, GameObject *obj2);
    SpaceClient *spaceClient;
};
#endif /*__SCENE1_H__*/