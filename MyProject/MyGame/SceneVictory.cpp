#include"SceneVictory.h"
#include "SpaceCraft.h"

#include "Cliente/SpaceClient.h"
#include "../SDL_Utils/Text.h"

SceneVictory::SceneVictory(SDL_Renderer* renderer, SpaceClient *spaceClient_, int idWinner):Scene(renderer),spaceClient(spaceClient_) //
{

    std::string winMessage = "PLAYER " + std::to_string(idWinner) + " WINS!!!";
    Text *t = new Text();
    t->setText(renderer, winMessage.c_str());
    t->setParams(150,220,350,50);
    texts.push_back(t);


    Text *info = new Text();
    info->setText(renderer, "PRESS SPACE TO REPLAY");
    info->setParams(220,370,200,25);
    texts.push_back(info);

    GameObject *backGround = new GameObject(renderer, spaceClient_);
    backGround->setImage("Assets/WinMenu.png", 0, 0, 106, 80);
    backGround->setScale(6.1,6.1);
    backGround->setPosition(0, 0);
    go.push_back(backGround);

}

void SceneVictory::handleEvent(const SDL_Event &e){
    

    if (e.type == SDL_KEYDOWN){

		int action;

        switch (e.key.keysym.sym)
        {
            case SDLK_SPACE: 
                action=5; 
                spaceClient->sendMessage(action);             
            break;
        }
     
	}
}