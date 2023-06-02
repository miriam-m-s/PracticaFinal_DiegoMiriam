#include "SpaceClient.h"
#include <SDL2/SDL.h>
#include <string>
#include <cmath>
#include <iostream>
#include <fstream>

#include"../../SDL_Utils/GameObject.h"
#include"../../SDL_Utils/Text.h"
#include "../../SDL_Utils/Environment.h"
#include "../../SDL_Utils/Vector2D.h"
#include"../Scene1.h"
#include"../SceneLobby.h"
#include"../SpaceCraft.h"
#include"../BackGroundLobby.h"
#include"../Lava.h"
#include"../Enemy.h"
#include"../Tierra.h"
#include"../Victory.h"
#include"../GameManager.h"
#include "../../../RedUtils/Message.h"
#include "../SceneVictory.h"

const int FILAS = 15; //10
const int COLUMNAS = 16; //16

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
    backGround->setImage("Assets/Lobby.png", 0, 0, 640, 480);
    backGround->setScale(6.1,6.1);
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
    std::ifstream archivo("Assets/mapa.txt");  // Abrir el archivo para lectura
    
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
      
    }
    
    char mapa[FILAS][COLUMNAS];  // Matriz para almacenar el mapa
    
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            archivo >> mapa[i][j];  // Leer cada caracter en la posición correspondiente de la matriz
        }
    }
    
    archivo.close();  // Cerrar el archivo
    
    // Procesar el mapa
    std::vector<Vector2D> enemiesPos;

    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            char caracter = mapa[i][j];
            
            if (caracter == '0') {
                //Hacer algo si el carácter es '0'
                Lava* lava = new Lava(renderer,this);
                lava->setImage("Assets/lava.png", 0, 0,16,16 );
                lava->setScale(2.5,2.5);
                lava->setPosition(j * 16*2.5, i * 16*2.5);
                scene->addObject(lava);

            } else if (caracter == 'x') {
                Tierra* ter = new Tierra(renderer,this);
                ter->setImage("Assets/suelo.png", 0, 0,16,16 );
                ter->setScale(2.5,2.5);
                ter->setPosition(j * 16*2.5, i * 16*2.5);
                scene->addObject( ter);
            } 
            else if(caracter == 'R') {
                Victory* ter = new Victory(renderer,this);
                ter->setImage("Assets/victort.png", 0, 0,16,16 );
                ter->setScale(2.5,2.5);
                ter->setPosition(j * 16*2.5, i * 16*2.5);
                scene->addObject( ter);
            }
            else if(caracter == 'B') {
                Tierra* ter = new Tierra(renderer,this);
                ter->setImage("Assets/suelo.png", 0, 0,16,16 );
                ter->setScale(2.5,2.5);
                ter->setPosition(j* 16*2.5, i * 16*2.5);
                scene->addObject(ter);
                enemiesPos.push_back(Vector2D(j * 16*2.5, i * 16*2.5));
            }
        }
    }

    for(int i=0;i<enemiesPos.size();i++){
        Enemy* enemy = new Enemy(renderer,this);
        enemy->setImage("Assets/mounstruo.png", 0, 0, 24, 20);
        enemy->setScale(1,1);
        enemy->setID(myID);
        enemy->setIndex(enemies.size());
        enemy->setPosition(enemiesPos[i].getX(), enemiesPos[i].getY()+10);
        scene->addObject(enemy);
        enemies.push_back(enemy);
    }
   
    if(myID == 0){
        spaceCrafts[0]=new SpaceCraft(renderer,this);
        spaceCrafts[0]->setImage("Assets/ship0selected.png", 0, 0, 10, 10);
        spaceCrafts[0]->setScale(3,3);
        spaceCrafts[0]->setPosition(0,environment().height() - spaceCrafts[0]->GetHeight() - 10);
        spaceCrafts[0]->setIniPos(0,environment().height() - spaceCrafts[0]->GetHeight() - 10);
        scene->addObject(spaceCrafts[0]);
        
        spaceCrafts[1]=new SpaceCraft(renderer,this);
        spaceCrafts[1]->setImage("Assets/ship1.png", 0, 0, 10, 10);
        spaceCrafts[1]->setScale(3,3);
        spaceCrafts[1]->setPosition(environment().width() - spaceCrafts[1]->GetWidth(),environment().height() - spaceCrafts[1]->GetHeight() - 10);
        spaceCrafts[1]->setIniPos(environment().width() - spaceCrafts[1]->GetWidth(),environment().height() - spaceCrafts[1]->GetHeight() - 10);
        scene->addObject( spaceCrafts[1]);
    }

    else {

        spaceCrafts[0]=new SpaceCraft(renderer,this);
        spaceCrafts[0]->setImage("Assets/ship0.png", 0, 0, 10, 10);
        spaceCrafts[0]->setScale(3,3);
        spaceCrafts[0]->setPosition(0,environment().height() - spaceCrafts[0]->GetHeight() - 10);
        spaceCrafts[0]->setIniPos(0,environment().height() - spaceCrafts[0]->GetHeight() - 10);
        scene->addObject(spaceCrafts[0]);
        
        spaceCrafts[1]=new SpaceCraft(renderer,this);
        spaceCrafts[1]->setImage("Assets/ship1selected.png", 0, 0, 10, 10);
        spaceCrafts[1]->setScale(3,3);
        spaceCrafts[1]->setPosition(environment().width() - spaceCrafts[1]->GetWidth(),environment().height() - spaceCrafts[1]->GetHeight() - 10);
        spaceCrafts[1]->setIniPos(environment().width() - spaceCrafts[1]->GetWidth(),environment().height() - spaceCrafts[1]->GetHeight() - 10);
        scene->addObject( spaceCrafts[1]);

    }

    scenes_.pop();
    scenes_.push(scene);    
}

void SpaceClient::input_thread()
{

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

    if(!ejected) logout();
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
        else if(message_.type == Message::MessageType::READY){
            backGround->recieveMesage(Message::MessageType::READY);
        }
        else if (message_.type == Message::MessageType::PLAYING){
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
        else if(message_.type == Message::MessageType::EJECT){
            salir=true;
            ejected = true;
        }
        else if(message_.type == Message::MessageType::COLLISION){
            GameObject *obj1 = scenes_.front()->getObjFromGo((int)message_.indexObj1);
            GameObject *obj2 = scenes_.front()->getObjFromGo((int)message_.indexObj2);
            if(obj1 != nullptr && obj2 != nullptr){
                obj1->OnCollision(obj2);
                obj2->OnCollision(obj1);
            }
        }
        else if(message_.type == Message::MessageType::MOVEENEMY){
            enemies[(int)message_.indexObj1]->move(message_.newPosX, message_.flipOfObj);
        }
    }
}

void SpaceClient::sendAction(int action, int shipMoved){

    Message::Input act;

    switch (action)
    {
    case 0:
        act=Message::Input::DOWN;
        break;
    case 1:
        act=Message::Input::LEFT;
        break;
    case 2:
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

        Message::MessageType act;
        switch (action)
         {
            case 0:
                act=Message::MessageType::LOGIN;
                break;
            case 1:
                act=Message::MessageType::MESSAGE;
                break;
            case 2:
                act=Message::MessageType::LOGOUT;
            break;
            case 3:
                act=Message::MessageType::INPUT;
            break;
            case 4:
                act=Message::MessageType::READY;
            break;
            case 5:
                act=Message::MessageType::PLAYING;
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

void SpaceClient::moveEnemies(int newPosx_, int index, int flip){

    Message em;
    em.type = Message::MOVEENEMY;
    em.newPosX = newPosx_;
    em.indexObj1 =uint8_t(index);
    em.flipOfObj = flip;

    //mandamos mensaje al servidor
    socket.send(em, socket);   
}

void SpaceClient::someoneWins(int id){

    //Creamos la escena de victoria
    SceneVictory* scene = new SceneVictory(renderer,this, id);
    scenes_.pop();
    scenes_.push(scene);

}
