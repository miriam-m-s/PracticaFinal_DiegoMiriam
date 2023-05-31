#include "SpaceClient.h"
#include <SDL2/SDL.h>
#include <string>
#include <cmath>

#include"../../SDL_Utils/GameObject.h"
#include"../../SDL_Utils/Text.h"
#include "../../SDL_Utils/Environment.h"
#include"../Scene1.h"
#include"../SceneLobby.h"
#include"../SpaceCraft.h"
#include"../BackGroundLobby.h"
#include"../GameManager.h"
#include "../../../RedUtils/Message.h"

void SpaceClient::login()
{

    //INICIALIZACION JUEGO SDL
    Environment::init(nick, 640, 480);

    renderer = environment().renderer();

    // Establecer el color de fondo del renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

   callSceneLobby();
    
    std::string msg;
    Message em(nick, msg);
    em.type = Message::LOGIN;
    socket.send(em, socket);
}

void SpaceClient::callSceneLobby(){

    //Creamos la escena de espera
    SceneLobby* scene = new SceneLobby(renderer,this);
    Text *t = new Text();
    t->setText(renderer, "WAITING CLIENT...");
    t->setParams(120,370,400,50);
    scene->addText(t);

    backGround = new BackGroundLobby(renderer, this,t);
    backGround->setImage("Assets/fondo2.jpg", 0, 0, 640, 480);
    scene->addObject(backGround);

    scenes_.push(scene);
}

void SpaceClient::logout()
{
    std::string msg;

    Message em(nick, msg);
    em.type = Message::LOGOUT;

    socket.send(em, socket);
    
}

void SpaceClient::play(){

    Scene1 *scene = new Scene1(renderer, this);
    GameObject* fondo=new GameObject(renderer, this);
    fondo->setImage("Assets/FONDO.jpg", 0, 0, 640, 480);
    //scene->addObject(fondo);

    
    spaceCrafts[0]=new SpaceCraft(renderer,this);
    spaceCrafts[0]->setImage("Assets/naves.png", 8, 16, 8, 8);
    spaceCrafts[0]->setScale(0.5,0.5);
    spaceCrafts[0]->setPosition(0,environment().height() - spaceCrafts[0]->GetHeight() - 10);
    spaceCrafts[0]->setIniPos(0,environment().height() - spaceCrafts[0]->GetHeight() - 10);
    scene->addObject(spaceCrafts[0]);
    
    spaceCrafts[1]=new SpaceCraft(renderer,this);
    spaceCrafts[1]->setImage("Assets/naves.png", 8, 8, 8, 8);
    spaceCrafts[1]->setScale(0.5,0.5);
    spaceCrafts[1]->setPosition(environment().width() - spaceCrafts[1]->GetWidth(),environment().height() - spaceCrafts[1]->GetHeight() - 10);
    spaceCrafts[1]->setIniPos(environment().width() - spaceCrafts[1]->GetWidth(),environment().height() - spaceCrafts[1]->GetHeight() - 10);
    scene->addObject( spaceCrafts[1]);

    scenes_.pop();
    scenes_.push(scene);    
}

void SpaceClient::input_thread()
{
    bool salir = false;
    GameManager& gameManager = GameManager::getInstance();

    gameManager.initialize();
    Uint32 prevTime = SDL_GetTicks();
    SDL_Event event;

    while (!salir) {
		Uint32 startTime = environment().currRealTime();
		while (SDL_PollEvent(&event))
		{
			// Salir del server
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				salir=true;
				continue;
			}

			
            scenes_.front()->handleEvent(event);
		}
        
        // Calcula el deltaTime
        Uint32 currTime = SDL_GetTicks();
        float deltaTime = (currTime - prevTime) / 1000.0f;
        prevTime = currTime;	
        	
		scenes_.front()->update(deltaTime);
        if(myID == 0)scenes_.front()->handleCollision();
        scenes_.front()->elim();
        

		environment().clearRenderer({0, 30, 160});

		scenes_.front()->render();
     

		environment().presentRenderer();

		Uint32 frameTime = environment().currRealTime() - startTime;
		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
        Uint32 endTime = SDL_GetTicks(); // Registra el tiempo actual nuevamente
    }

    logout();
}

void SpaceClient::net_thread()
{
    Message message_;
    Socket* sock_ = new Socket(socket);
    while(true)
    {
        //Recibir Mensajes de red
        socket.recv(message_, sock_);

        if(message_.type == Message::MessageType::LOGIN){
            myID = message_.idClient;
        }
        else if(message_.type == Message::MessageType::WAITING){
            backGround->recieveMesage(Message::MessageType::WAITING);
        }
        else if (message_.type == Message::MessageType::READY){
            play();
            spaceCrafts[myID]->setID(myID);
            spaceCrafts[1 - myID]->setID(1 - myID);
        }
        else if (message_.type == Message::MessageType::LOGOUT){
            myID = message_.idClient;
            callSceneLobby();
            scenes_.pop();
        }
        else if(message_.type == Message::MessageType::INPUT){
            int input = message_.input;
            //Me muevo yo
            if(message_.shipMoved == myID){
                spaceCrafts[myID]->moveShip(input);
            }
            //Se mueve el otro
            else spaceCrafts[1-myID]->moveShip(input);
            
        }
        else if(message_.type == Message::MessageType::COLLISION){
            GameObject *obj1 = scenes_.front()->getObjFromGo((int)message_.indexObj1);
            GameObject *obj2 = scenes_.front()->getObjFromGo((int)message_.indexObj2);
            if(obj1 != nullptr && obj2 != nullptr){
                obj1->OnCollision(obj2);
                obj2->OnCollision(obj1);
            }
        }
    }
}

void SpaceClient::sendAction(int action, int shipMoved){

    Message::Input act;

    switch (action)
    {
    case 0://tecla space
        act=Message::Input::DOWN;
        break;
    case 1:
        act=Message::Input::LEFT;
        break;
    case 2://tecla derecha
        act=Message::Input::RIGHT;
      break;
    case 3:
        act=Message::Input::UP;
    }

    Message em;
    em.type = Message::INPUT;
    em.input = act;
    em.shipMoved = shipMoved;

    //mandamos mensaje al servidor
    socket.send(em, socket);   
}

void SpaceClient:: sendMessage(int action){

         Message::MessageType act;;
        switch (action)
         {
            case 0://tecla space
                act=Message::MessageType::LOGIN;
                break;
            case 1:
                act=Message::MessageType::MESSAGE;
                break;
            case 2://tecla derecha
                act=Message::MessageType::LOGOUT;
            break;
            case 3://tecla derecha
                act=Message::MessageType::INPUT;
            break;
            case 4://tecla derecha
                act=Message::MessageType::WAITING;
            break;
            case 5://tecla derecha
                act=Message::MessageType::READY;
            break;
        }
        Message em;
        em.type = act;
        socket.send(em, socket);
    
   
}

void SpaceClient::addGameObjectToScene(GameObject *obj){
    scenes_.front()->addObject(obj);
}

void SpaceClient::collisionProduced(int indexObj1_, int indexObj2_){

    Message em;
    em.type = Message::COLLISION;
    em.indexObj1 = uint8_t(indexObj1_);
    em.indexObj2 = uint8_t(indexObj2_);

    //mandamos mensaje al servidor
    socket.send(em, socket);   
}
