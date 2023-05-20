#ifndef __SPACECRAFT_H__
#define __SPACECRAFT_H__
#include"../SDL_Utils/GameObject.h"

class SpaceCraft:public GameObject{
    public:
    SpaceCraft(SDL_Renderer* renderer);
    
    virtual void handleInput(const SDL_Event &event);
    ~SpaceCraft();
    private:
    SDL_Scancode left_, right_;
};
#endif /*__GAMEOBJECT_H__*/