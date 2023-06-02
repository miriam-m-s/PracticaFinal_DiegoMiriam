#include "GameObject.h"
#include <iostream>
#include "../MyGame/Cliente/SpaceClient.h"
#include"Environment.h"

GameObject::GameObject(SDL_Renderer* renderer, SpaceClient *spaceClient_):renderer_(environment().renderer()), spaceClient(spaceClient_){
    tr=new Transform();
    img_= new Image();
    flip = SDL_FLIP_NONE;
}

void GameObject::setPosition(int x,int y){
    tr->SetPosition(x,y);
}

void GameObject::setRotation(float rot){
     tr->setRotation(rot);
}

void GameObject::update(float deltaTime){

}

void GameObject::Render(){
    auto texture=img_->getTexture();
    if (texture != nullptr) {
            
        SDL_Rect clipRect = { img_->getX(), img_->getY(), img_->getWidht(), img_->getHeight() };
        SDL_Rect destRect = { tr->GetPositionX(), tr->GetPositionY(), (int)(img_->getTexWidht()*tr->GetScaleX()), (int)(img_->getTexHeight()*tr->GetScaleY())};
        SDL_RenderCopyEx(renderer_, texture, &clipRect,&destRect,tr->getRotation(),nullptr,flip);
    }

   
}

void GameObject::setImage(const std::string& filePath, int x, int y, int width, int height){
    img_->setImage(renderer_,filePath,x,y,width,height);
    SDL_Event evento;
}
void GameObject::setScale(float scalex,float scaley){
    tr->SetScale(scalex,scaley);
}
GameObject::~GameObject() {
   delete img_;
   delete tr;
}