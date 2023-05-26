#ifndef __SCENE_H__
#define __SCENE_H__
#include <SDL2/SDL.h>
#include<vector>
#include "GameObject.h"
#include "Text.h"

class Scene {
public:
    Scene(SDL_Renderer* renderer):renderer_(renderer) {};
    ~Scene();
    virtual void update();
    virtual void render();
    virtual void handleEvent(const SDL_Event& event);
    virtual void addObject(GameObject* gameObject);
protected:
    std::vector<GameObject*>go;
    std::vector<Text*>texts;
    SDL_Renderer* renderer_;
};
#endif /*__SCENE_H__*/