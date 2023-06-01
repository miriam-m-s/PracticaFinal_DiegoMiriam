#include"SceneVictory.h"
#include "SpaceCraft.h"
#include "BackGroundVictory.h"

#include "Cliente/SpaceClient.h"
#include "../SDL_Utils/Text.h"

SceneVictory::SceneVictory(SDL_Renderer* renderer, SpaceClient *spaceClient_, int idWinner):Scene(renderer) //
{

    // std::string winMessage = "PLAYER" + std::to_string(idWinner) + "WINS!!!"
    // Text *t = new Text();
    // t->setText(renderer, winMessage);
    // t->setParams(120,370,400,50);
    // texts.push_back(t);


    // Text *info = new Text();
    // info->setText(renderer, "PRESS SPACE TO START");
    // info->setParams(120,270,200,25);
    // texts.push_back(info);

}