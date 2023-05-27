#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include"Image.h"

class Transform {
public:
    Transform()
        : positionX(0), positionY(0),rotation_(0) {}

    void SetPosition(float x, float y) {
        positionX = x;
        positionY = y;
    }
    void SetScale(float x, float y) {
        scaleX = x;
        scaleY = y;
    }
    float GetPositionX() const {
        return positionX;
    }

    float GetPositionY() const {
        return positionY;
    }
    void setRotation(float ror){
         rotation_=ror;
    }

    float GetScaleX() const {
        return scaleX;
    }

    float GetScaleY() const {
        return scaleY;
    }
    float getRotation(){
        return rotation_;
    }

private:
    float positionX;
    float positionY;
    float rotation_;
    float scaleX=1,scaleY=1;
};

class SpaceClient;

class GameObject{
public:
    GameObject(SDL_Renderer* renderer, SpaceClient *spaceClient_); //
    void setPosition(float x,float y);
    void setRotation(float rot);
    void setScale(float scalex,float scaley);
    void setImage(const std::string& filePath, int x, int y, int width, int height);
     void Render();
    virtual void update(float deltaTime);
    virtual void handleInput(const SDL_Event &event) {};
    Transform* getTransform(){
        return tr;
    }
    ~GameObject();
protected:
    Image* img_;
    Transform* tr;
    SDL_Renderer* renderer_;
    SpaceClient *spaceClient;
};
#endif /*__GAMEOBJECT_H__*/