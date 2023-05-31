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
#include"../Enemy1.h"
#include"../Enemy2.h"
#include"../Enemy3.h"
#include"../Bala.h"
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
    scene->addObject(spaceCrafts[0]);
    
    spaceCrafts[1]=new SpaceCraft(renderer,this);
    spaceCrafts[1]->setImage("Assets/naves.png", 8, 8, 8, 8);
    spaceCrafts[1]->setScale(0.5,0.5);
    spaceCrafts[1]->setPosition(environment().width() - spaceCrafts[1]->GetWidth(),environment().height() - spaceCrafts[1]->GetHeight() - 10);
    scene->addObject( spaceCrafts[1]);

    //Anchos disponible de la ventana quitando margenes
    int availableWidth = environment().width() - 2*enemiesOffset;
    int numEnemies = (int)(availableWidth / spaceCrafts[1]->GetWidth());
    // Calcular el margen adicional para ambos lados
    int aditionalOffset = (availableWidth - (numEnemies * spaceCrafts[1]->GetWidth())) / numEnemies-1;
    // Calcular el espacio total ocupado por las imágenes y los márgenes
    int totalSpace = (spaceCrafts[1]->GetWidth() * numEnemies) + (aditionalOffset * (numEnemies - 1));
    // Calcular el margen adicional izquierdo para centrar las imágenes
    int leftOffset = (environment().width() - totalSpace) / 2;

    int positionX = leftOffset;
    int positionY = enemiesOffset*4;

    mainEnemy = new Enemy(renderer, this);
    mainEnemy->setPosition(positionX - 5, -2*positionY);
    //HACER UN SET VISIBLE PARA QUITAR LA RENDEREIZACION Y ARREGLAR PROBLEMA AL METER LOS DEMÁS ALIENS
    mainEnemy->setImage("Assets/bala.jpg", 0, 0, 8, 8);
    mainEnemy->setScale(123, 5);
    mainEnemy->setID(myID);
    scene->addObject(mainEnemy);

    Enemy1 *enemy1;

    for(int i = 0; i < numEnemies; i++){
        enemy1 = new Enemy1(renderer,this);
        enemy1->setImage("Assets/naves.png", 40, 0, 8, 8);
        enemy1->setScale(0.5,0.5);
        enemy1->setPosition(positionX, positionY);
        
        mainEnemy->addEnemy(enemy1, Enemy::ENEMY1);
        scene->addObject(enemy1);
        positionX += aditionalOffset + enemy1->GetWidth();
    }

    // Enemy2 *enemy2;
    // positionX = leftOffset - 5;
    // positionY += enemy1->GetHeight();

    // for(int i = 0; i < 2*numEnemies; i++){

    //     if(i == numEnemies){
    //         positionY += enemy1->GetHeight();
    //         positionX = leftOffset - 5;
    //     }

    //     enemy2 = new Enemy2(renderer,this);
    //     enemy2->setImage("Assets/naves.png", 72, 0, 8, 8);
    //     enemy2->setScale(0.5,0.5);
    //     enemy2->setPosition(positionX, positionY);

    //     mainEnemy->addEnemy(enemy2, Enemy::ENEMY2);
    //     scene->addObject(enemy2);
    //     positionX += aditionalOffset + enemy2->GetWidth();
    // }

    // Enemy3 *enemy3;
    // positionX = leftOffset - 5;
    // positionY += enemy2->GetHeight();

    // for(int i = 0; i < numEnemies; i++){

    //     enemy3 = new Enemy3(renderer,this);
    //     enemy3->setImage("Assets/naves.png", 32, 16, 8, 8);
    //     enemy3->setScale(0.5,0.5);
    //     enemy3->setPosition(positionX, positionY);

    //     mainEnemy->addEnemy(enemy3, Enemy::ENEMY3);
    //     scene->addObject(enemy3);
    //     positionX += aditionalOffset + enemy3->GetWidth();
    // }

    scenes_.pop();
    scenes_.push(scene);    
}

void SpaceClient::create_Bullet(int id){

   int x,y,w,h;
     x=spaceCrafts[1-myID]->GetPositionX();
        y=spaceCrafts[1-myID]->GetPositionY();
        w=spaceCrafts[1-myID]->GetWidth();
        h=spaceCrafts[1-myID]->GetHeight();
   if(id == myID){
        x=spaceCrafts[myID]->GetPositionX();
        y=spaceCrafts[myID]->GetPositionY();
        w=spaceCrafts[myID]->GetWidth();
        h=spaceCrafts[myID]->GetHeight();
    }               
   
    auto bullet=new Bala(environment().renderer(),this);

    bullet->setScale(0.25, 0.25);
    bullet->setPosition(x+w/2 - bullet->GetWidth()/2,y);
    bullet->setFromPlayer(true);

    scenes_.front()->addObject(bullet);
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
            if(input!=Message::Input::SPACE){
                //Me muevo yo
                if(message_.shipMoved == myID){
                    spaceCrafts[myID]->moveShip(input);
                }
                //Se mueve el otro
                else spaceCrafts[1-myID]->moveShip(input);
            }
            
            else if(input==Message::Input::SPACE){
                std::cout<<"disparando "<<std::endl;
                create_Bullet(message_.shipMoved );  
            }         
        }
        else if(message_.type == Message::MessageType::SHOOTENEMY){
            mainEnemy->orderShoot(message_.typeEnemy, message_.enemySelected);
        }
        else if(message_.type == Message::MessageType::COLLISION){
            std::cout << "recibido objeto 1: " << (int)message_.indexObj1 << std::endl;
            std::cout << "recibido objeto 2: " << (int)message_.indexObj2 << std::endl;
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

    Message::Input act=Message::Input::SPACE;

    switch (action)
    {
    case 0://tecla space
        act=Message::Input::SPACE;
        break;
    case 1:
        act=Message::Input::LEFT;
        break;
    case 2://tecla derecha
        act=Message::Input::RIGHT;
      break;
    }

    std::string msg;
    Message em(nick, msg);
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

void SpaceClient::enemyHasToShoot(int enemySelected_, int typeEnemy_){
    Message em;
    em.type = Message::SHOOTENEMY;
    em.enemySelected = enemySelected_;
    em.typeEnemy = typeEnemy_;

    //mandamos mensaje al servidor
    socket.send(em, socket);   
}

void SpaceClient::collisionProduced(int indexObj1_, int indexObj2_){

    Message em;
    em.type = Message::COLLISION;
    em.indexObj1 = uint8_t(indexObj1_);
    em.indexObj2 = uint8_t(indexObj2_);

    //mandamos mensaje al servidor
    socket.send(em, socket);   
}
