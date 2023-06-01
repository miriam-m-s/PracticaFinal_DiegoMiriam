#ifndef __ENEMY_H__
#define __ENEMY_H__
#include"../SDL_Utils/GameObject.h"

//class SpaceClient;
class GameObject;

class Enemy:public GameObject{
public:
    Enemy(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer,spaceClient){
    };
    ~Enemy();

    virtual void OnCollision(GameObject *other);
    void setID(int id);
    void setIndex(int index_);
    void update(float deltaTime);
    void move(int x, int flip_);

private:
    int direction = 1;
    int velocity = 1;
    int velocityAuxiliar = 10;
    int myID;   
    int index;    
};
#endif /*__GAMEOBJECT_H__*/