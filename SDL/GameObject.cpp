#include "GameObject.h"
GameObject::GameObject(SDL_Renderer* renderer):renderer_(renderer){
    tr=new Transform();
    img_=new Image();
}
void GameObject::setPosition(float x,float y){
    tr->SetPosition(x,y);
}
void GameObject::setRotation(float rot){
     tr->setRotation(rot);
}
void GameObject::setImage(const std::string& filePath, int x, int y, int width, int height){
    img_->setImage(renderer_,filePath,x,y,width,height);
}
void GameObject::setScale(float scalex,float scaley){
    tr->SetScale(scalex,scaley);
}
GameObject::~GameObject() {
   delete img_;
   delete tr;
}