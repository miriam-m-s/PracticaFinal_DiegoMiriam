#include "SpaceCraft.h"
#include<iostream>
SpaceCraft::SpaceCraft(SDL_Renderer* renderer):GameObject(renderer){

}
void SpaceCraft:: handleInput(const SDL_Event &e){
    

    if (e.type == SDL_KEYDOWN ){
		
        switch (e.key.keysym.sym)
                {
                    case SDLK_a:                      
                         tr->SetPosition(tr->GetPositionX()-5,tr->GetPositionY());
                        break;

                    case SDLK_d:                       
                          tr->SetPosition(tr->GetPositionX()+5,tr->GetPositionY());
                        break;
                }
        
        
	}
}