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

    void SetPosition(int x, int y) {
        positionX = x;
        positionY = y;
    }
    void Translate(int x, int y){
        positionX += x;
        positionY += y;
    }
    void SetScale(float x, float y) {
        scaleX = x;
        scaleY = y;
    }
    int GetPositionX() const {
        return positionX;
    }

    int GetPositionY() const {
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
    int positionX;
    int positionY;
    float rotation_;
    float scaleX=1,scaleY=1;
};

class SpaceClient;

class GameObject{
public:
    GameObject(SDL_Renderer* renderer, SpaceClient *spaceClient_); //
    void setPosition(int x,int y);
    void setRotation(float rot);
    void setScale(float scalex,float scaley);
    void setImage(const std::string& filePath, int x, int y, int width, int height);
     virtual void Render();
    virtual void update(float deltaTime);
     int GetPositionX() const {
        return tr->GetPositionX();
    }
    int GetWidth() const {
        // std::cout << "Width Text: " <<  img_->getTexWidht() << std::endl;    
        // std::cout << "Scale X: " <<  tr->GetScaleX() << std::endl;

        return(img_->getTexWidht()*tr->GetScaleX());
    }
    int GetHeight() const {
        // std::cout << "Height Text: " <<  img_->getTexHeight() << std::endl;    
        // std::cout << "Scale Y: " <<  tr->GetScaleY() << std::endl;
        return(img_->getTexHeight()*tr->GetScaleY());
    }
    int GetPositionY() const {
        return tr->GetPositionY();
    }
    virtual void handleInput(const SDL_Event &event) {};
    Transform* getTransform(){
        return tr;
    }
    inline bool isEnabled() const {
		return enabled_;
	}
    virtual void OnCollision(GameObject *other){}
	inline bool setEnabled(bool e) {
		return enabled_ = e;
	}
    ~GameObject();
protected:
    bool enabled_=true;
    Image* img_;
    Transform* tr;
    SDL_Renderer* renderer_;
    SpaceClient *spaceClient;
};
#endif /*__GAMEOBJECT_H__*/