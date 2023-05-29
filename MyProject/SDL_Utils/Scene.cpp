#include"Scene.h"
#include <algorithm>  // Para std::remove_if
void Scene::update(float deltaTime){
    for(auto &obj:go){
        obj->update(deltaTime);
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
void Scene::elim(){

	go.erase(std::remove_if(go.begin(), go.end(),

							   [](const GameObject *e)
							   {
								    if (e->isEnabled())
									    return false;
								    else
								    {
								 	    if (e != nullptr)
									    {
								 		    delete e;
										    e = nullptr;
										    return true;
									    }
									    else
										    return false;
								   }
							   }),
				go.end());
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