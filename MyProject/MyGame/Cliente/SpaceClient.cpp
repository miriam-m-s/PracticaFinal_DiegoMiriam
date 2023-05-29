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
#include"../Enemy.h"
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

    //Creamos la escena y naves
    SceneLobby* scene = new SceneLobby(renderer,this);
    Text *t = new Text();
    t->setText(renderer, "WAITING CLIENT...");
    t->setParams(120,370,400,50);
    scene->addText(t);

    backGround = new BackGroundLobby(renderer, this,t);
    backGround->setImage("Assets/fondo2.jpg", 0, 0, 640, 480);
    scene->addObject(backGround);
    

    std::string msg;

    Message em(nick, msg);
    em.type = Message::LOGIN;
    socket.send(em, socket);

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
    scene->addObject(fondo);
    
    spaceCrafts[0]=new SpaceCraft(renderer,this);
    spaceCrafts[0]->setImage("Assets/naves.png", 8, 0, 8, 8);
    spaceCrafts[0]->setScale(0.5,0.5);
    spaceCrafts[0]->setPosition(0,environment().height() - spaceCrafts[0]->GetHeight());
    scene->addObject(spaceCrafts[0]);
    
    spaceCrafts[1]=new SpaceCraft(renderer,this);
    spaceCrafts[1]->setImage("Assets/naves.png", 8, 8, 8, 8);
    spaceCrafts[1]->setScale(0.5,0.5);
    spaceCrafts[1]->setPosition(environment().width() - spaceCrafts[1]->GetWidth(),environment().height() - spaceCrafts[1]->GetHeight());
    scene->addObject( spaceCrafts[1]);

    Enemy *enemy;

    //Anchos disponible de la ventana quitando margenes
    int availableWidth = environment().width() - 2*enemiesOffset;

    double numEnemies = std::floor(availableWidth / spaceCrafts[1]->GetWidth());

    // Calcular el margen adicional para ambos lados
    int aditionalOffset = (availableWidth - (numEnemies * spaceCrafts[1]->GetWidth())) / numEnemies-1;

    // Calcular el espacio total ocupado por las imágenes y los márgenes
    int totalSpace = (spaceCrafts[1]->GetWidth() * numEnemies) + (aditionalOffset * (numEnemies - 1));

    // Calcular el margen adicional izquierdo para centrar las imágenes
    int leftOffset = (environment().width() - totalSpace) / 2;

    int positionX = leftOffset;

    // for(int i = 0; i < numEnemies; i++){
    //     enemy = new Enemy(renderer,this);
    //     enemy->setImage("Assets/naves.png", 40, 0, 8, 8);
    //     enemy->setScale(0.5,0.5);
    //     enemy->setPosition(positionX, enemiesOffset);
    //     scene->addObject(enemy);
    //     positionX += aditionalOffset + enemy->GetWidth();
    //     enemies.push_back(enemy);
    // }

    scenes_.pop();
    scenes_.push(scene);

}

void SpaceClient::create_Bullet(int id){

   int x,y,w,h;
   if(id == myID){
        x=spaceCrafts[myID]->GetPositionX();
        y=spaceCrafts[myID]->GetPositionY();
        w=spaceCrafts[myID]->GetWidth();
        h=spaceCrafts[myID]->GetHeight();
    }               
    else {
        x=spaceCrafts[1-myID]->GetPositionX();
        y=spaceCrafts[1-myID]->GetPositionY();
        w=spaceCrafts[1-myID]->GetWidth();
        h=spaceCrafts[1-myID]->GetHeight();
    }

    auto bala=new Bala(environment().renderer(),this);
    bala->setImage("Assets/bala.jpg", 0, 0, 5, 5);
    bala->setPosition(x+w/2,y);
    bullets.push_back(bala);
    scenes_.front()->addObject(bala);
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
        //checkCollisions();
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
            
            else create_Bullet(message_.shipMoved );          
        }


     
    }
}

void SpaceClient::sendAction(int action, int shipMoved){

   if(myID == shipMoved){

    Message::Input act;;

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
void SpaceClient::checkCollisions(){

    bool collision;

    for(auto bullet = bullets.begin(); bullet != bullets.end();){

        collision = false;

        if((*bullet) != nullptr){
            
            for(auto enemie = enemies.begin(); enemie != enemies.end();){

                if(checkCollision(*bullet, *enemie)){
                    
                    (*bullet)->setEnabled(false);
                    (*enemie)->setEnabled(false);
                    

                    enemie = enemies.erase(enemie);
                    bullet = bullets.erase(bullet);

                    collision = true;
                }

                else enemie++;

            }

            //bullet++;

            if(!collision){
                bullet++;
            }

        }

        else{
            bullet = bullets.erase(bullet);
        }
    }


}

bool SpaceClient::checkCollision(GameObject *obj1, GameObject *obj2){

    // Calcular los límites de las cajas de colisión para ambas entidades
    float left1 = obj1->GetPositionX();
    float right1 =  obj1->GetPositionX() +  obj1->GetWidth();
    float top1 =  obj1->GetPositionY();
    float bottom1 =  obj1->GetPositionY() +  obj1->GetHeight();

    float left2 =  obj2->GetPositionX();
    float right2 =  obj2->GetPositionX() + obj2->GetWidth();
    float top2 = obj2->GetPositionY();
    float bottom2 = obj2->GetPositionY() + obj2->GetHeight();

    // Comprobar la colisión entre las cajas de colisión
    if (right1 >= left2 && left1 <= right2 && bottom1 >= top2 && top1 <= bottom2) {
        return true;
    }

    // No hay colisión
    return false;

}