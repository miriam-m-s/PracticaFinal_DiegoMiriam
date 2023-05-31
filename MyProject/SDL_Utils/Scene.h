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
    virtual void update(float deltaTime);
    virtual void render();
    virtual void handleEvent(const SDL_Event& event);
    virtual void handleCollision() {};
    virtual void addObject(GameObject* gameObject);
    virtual void addText(Text* txt);
    virtual void elim();
    GameObject *getObjFromGo(int index);
protected:
    std::vector<GameObject*>go;
    std::vector<Text*>texts;
    SDL_Renderer* renderer_;
    int index = 0;
};
#endif /*__SCENE_H__*/