#pragma once
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
    float scaleX,scaleY;
};
class GameObject{
    public:
    GameObject(SDL_Renderer* renderer);
    void setPosition(float x,float y);
    void setRotation(float rot);
    void setScale(float scalex,float scaley);
    void setImage(const std::string& filePath, int x, int y, int width, int height);
     void Render() {
        auto texture=img_->getTexture();
        if (texture != nullptr) {
            SDL_Rect destRect = { static_cast<int>(tr->GetPositionX()), static_cast<int>(tr->GetPositionY()), int(img_->getTexWidht()*tr->GetScaleX()), int(img_->getTexHeight()*tr->GetScaleY()) };
            SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
            SDL_RenderCopy(renderer_, texture, nullptr, &destRect);
        }
    }
    Transform* getTransform(){
        return tr;
    }
    ~GameObject();
    private:
    Image* img_;
    Transform* tr;
    SDL_Renderer* renderer_;
};