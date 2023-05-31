#include"Scene1.h"
#include "SpaceCraft.h"
#include "Cliente/SpaceClient.h"
#include "../SDL_Utils/Text.h"

Scene1::Scene1(SDL_Renderer* renderer, SpaceClient *spaceClient_):Scene(renderer), spaceClient(spaceClient_) //
{
}

void Scene1::handleCollision(){
    int i = 0, j = 0;

    for(auto &object1 : go){
       for(auto &object2 : go){
            if(object1 != object2 && checkCollision(object1, object2)){
                spaceClient->collisionProduced(i, j);
            }
            j++;
       }
        i++;     
        j = 0;   
    }
   

}

bool Scene1::checkCollision(GameObject *obj1, GameObject *obj2){

    // o1 completely to the left of o2, or vice versa
	if (obj1->GetPositionX() + obj1->GetWidth() < obj2->GetPositionX()
			|| obj2->GetPositionX() + obj2->GetWidth() < obj1->GetPositionX()) {
		return false;
	}

	// o1 completely to the top of o2, or vice versa
	if (obj1->GetPositionY() + obj1->GetHeight() < obj2->GetPositionY()
			|| obj2->GetPositionY() + obj2->GetHeight()  < obj1->GetPositionY()) {
		return false;
	}

	return true;

}