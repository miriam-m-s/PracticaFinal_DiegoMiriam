#include"Scene.h"
void Scene::update(){
    for(auto &obj:go){
        obj->update();
    }
}
void Scene::render(){
    for(auto &obj:go){
        obj->Render();
    }
}
Scene::~Scene(){ 
    for(auto &obj:go){
        delete obj;
    }
}
void Scene::handleEvent(SDL_Event& event){
    for(auto &obj:go){
        obj->handleInput(event);
    }
}