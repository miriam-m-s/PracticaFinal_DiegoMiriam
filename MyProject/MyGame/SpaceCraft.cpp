#include "SpaceCraft.h"
#include<iostream>
#include "Cliente/SpaceClient.h"

SpaceCraft::SpaceCraft(SDL_Renderer* renderer, SpaceClient *spaceClient):GameObject(renderer, spaceClient){ //

}
void SpaceCraft:: handleInput(const SDL_Event &e){
    

    if (e.type == SDL_KEYDOWN ){
		int action;
        switch (e.key.keysym.sym)
        {
            case SDLK_a: 
                    action=1;                     
                    tr->SetPosition(tr->GetPositionX()-5,tr->GetPositionY());
                break;

            case SDLK_d:   
                    action=2;                    
                    tr->SetPosition(tr->GetPositionX()+5,tr->GetPositionY());
                break;
        }
        
        spaceClient->sendAction(action);
	}
}