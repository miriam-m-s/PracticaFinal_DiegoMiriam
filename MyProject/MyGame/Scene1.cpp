#include"Scene1.h"
#include "SpaceCraft.h"
#include "../SDL_Utils/Text.h"

Scene1::Scene1(SDL_Renderer* renderer, SpaceClient *spaceClient):Scene(renderer) //
{
     // SpaceCraft* ship=new SpaceCraft(renderer_, spaceClient);
     // ship->setImage("Assets/naves.png", 8, 0, 8, 8);
     // ship->setPosition(50,50);
     // ship->setScale(2,2);
     // ship->setRotation(30);
     // go.push_back(ship);

     Text *t = new Text();
     t->setText(renderer, "NAVE");
     t->setParams(200,200,50,50);
     texts.push_back(t);
}