#include"Scene1.h"
#include "SpaceCraft.h"
#include "../SDL_Utils/Text.h"

Scene1::Scene1(SDL_Renderer* renderer, SpaceClient *spaceClient):Scene(renderer) //
{
     Text *t = new Text();
     t->setText(renderer, "NAVE");
     t->setParams(200,200,50,50);
     texts.push_back(t);
}