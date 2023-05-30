#ifndef __SPACECRAFT_H__
#define __SPACECRAFT_H__
#include"../SDL_Utils/GameObject.h"
#include <vector>

//class SpaceClient;
class GameObject;
class SpaceCraft:public GameObject{
public:
    SpaceCraft(SDL_Renderer* renderer, SpaceClient *spaceClient); //
    
    virtual void handleInput(const SDL_Event &event);
    ~SpaceCraft();

    void moveShip(int input);
     virtual void Render();
    void setID(int id);
    void update(float deltaTime);
    virtual void OnCollision(GameObject *other);
private:
    int myID = 0;
    bool isShooting;
    float shootTimer = 0.0f;
    std::vector<GameObject*>hearts_;
};
#endif /*__GAMEOBJECT_H__*/
