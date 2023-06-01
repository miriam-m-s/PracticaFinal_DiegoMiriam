#include "Victory.h"
#include "SpaceCraft.h"


void Victory:: OnCollision(GameObject *other){
    
    SpaceCraft* spaceCraft = dynamic_cast<SpaceCraft*>(other);

    if(spaceCraft!=nullptr && !winner) {
        winner = true;
        //spaceClient->someoneWins(spaceCraft->getID());
    }
}