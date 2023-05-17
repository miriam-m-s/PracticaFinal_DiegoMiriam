#include "GameObject.h"
#include <iostream>
GameObject::GameObject(SDL_Renderer* renderer):renderer_(renderer){
    tr=new Transform();
    img_= new Image();
}
void GameObject::setPosition(float x,float y){
    tr->SetPosition(x,y);
}
void GameObject::setRotation(float rot){
     tr->setRotation(rot);
}
void GameObject::update(){

}
void GameObject::Render(){
     auto texture=img_->getTexture();
        if (texture != nullptr) {
             
            SDL_Rect clipRect = { img_->getX(), img_->getY(), img_->getWidht(), img_->getHeight() };
            SDL_Rect destRect = { static_cast<int>(tr->GetPositionX()), static_cast<int>(tr->GetPositionY()), int(img_->getTexWidht()*tr->GetScaleX()), int(img_->getTexHeight()*tr->GetScaleY()) };
            SDL_RenderCopyEx(renderer_, texture, &clipRect,&destRect,tr->getRotation(),nullptr,SDL_FLIP_NONE);
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