#include"SceneLobby.h"
#include "SpaceCraft.h"
#include "../SDL_Utils/Text.h"
#include "../SDL_Utils/GameObject.h"
#include "Bala.h"
#include "../SDL_Utils/Environment.h"

SceneLobby::SceneLobby(SDL_Renderer* renderer, SpaceClient *spaceClient):Scene(renderer) //
{
    // GameObject *backGround = new GameObject(renderer, spaceClient);
    // backGround->setImage("Assets/fondo2.jpg", 0, 0, 640, 480);
    // go.push_back(backGround);
    
    // Text *t = new Text();
    // t->setText(renderer, "WAITING CLIENT...");
    // t->setParams(120,370,400,50);
    // texts.push_back(t);
}