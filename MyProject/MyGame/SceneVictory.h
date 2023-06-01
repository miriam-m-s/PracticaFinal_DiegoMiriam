#ifndef __SCENEVICTORY_H__
#define __SCENEVICTORY_H__

#include"../SDL_Utils/Scene.h"
#include<vector>

class SpaceClient;

class SceneVictory: public Scene {
public:
    SceneVictory(SDL_Renderer* renderer, SpaceClient *spaceClient_, int idWinner); //
    ~SceneVictory(){};
    virtual void handleCollision() {};
};
#endif /*__SCENE1_H__*/