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
    for(auto &text:texts){
        text->Render();
    }
}
Scene::~Scene(){ 
    for(auto &obj:go){
        delete obj;
    }
}
void Scene::handleEvent(const SDL_Event& event){
    for(auto &obj:go){
        obj->handleInput(event);
        
    }
}
void Scene::addObject(GameObject* obj){
    go.push_back(obj);
}