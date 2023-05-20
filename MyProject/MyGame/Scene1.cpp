#include"Scene1.h"
#include "SpaceCraft.h"
Scene1::Scene1(SDL_Renderer* renderer):Scene(renderer)
{
     SpaceCraft* ship=new SpaceCraft(renderer_);
     ship->setImage("Assets/naves.png", 8, 0, 8, 8);
     ship->setPosition(50,50);
     ship->setScale(2,2);
     ship->setRotation(30);
     go.push_back(ship);
}