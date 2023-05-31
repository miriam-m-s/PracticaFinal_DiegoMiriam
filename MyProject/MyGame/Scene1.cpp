#include"Scene1.h"
#include "SpaceCraft.h"
#include "Bala.h"
#include "../SDL_Utils/Text.h"

Scene1::Scene1(SDL_Renderer* renderer, SpaceClient *spaceClient):Scene(renderer) //
{
}

void Scene1:: handleCollision(){
    for(auto object1 : go){
       for(auto object2 : go){
            if(checkCollision(object1, object2)){
                object2->OnCollision(object1);
                object1->OnCollision(object2);
            }
       }
        
    }
   

}

bool Scene1::checkCollision(GameObject *obj1, GameObject *obj2){

    // Calcular los límites de las cajas de colisión para ambas entidades
    float left1 = obj1->GetPositionX();
    float right1 =  obj1->GetPositionX() +  obj1->GetWidth();
    float top1 =  obj1->GetPositionY();
    float bottom1 =  obj1->GetPositionY() +  obj1->GetHeight();

    float left2 =  obj2->GetPositionX();
    float right2 =  obj2->GetPositionX() + obj2->GetWidth();
    float top2 = obj2->GetPositionY();
    float bottom2 = obj2->GetPositionY() + obj2->GetHeight();

    // Comprobar la colisión entre las cajas de colisión
    if (right1 >= left2 && left1 <= right2 && bottom1 >= top2 && top1 <= bottom2) {
        return true;
    }

    // No hay colisión
    return false;

}