#ifndef __SCENE1_H__
#define __SCENE1_H__
#include"../SDL_Utils/Scene.h"

class SpaceClient;

class Scene1: public Scene {
public:
    Scene1(SDL_Renderer* renderer, SpaceClient *spaceClient); //
    ~Scene1(){};
    void handleCollision();
private:
    bool checkCollision(GameObject *obj1, GameObject *obj2);
};
#endif /*__SCENE1_H__*/