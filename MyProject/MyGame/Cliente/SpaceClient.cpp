#include "SpaceClient.h"
#include <SDL2/SDL.h>
#include"../../SDL_Utils/GameObject.h"
#include "../../SDL_Utils/Environment.h"
#include <string>
#include"../Scene1.h"
#include"../SpaceCraft.h"
#include "../../../RedUtils/Message.h"

void SpaceClient::login()
{
    std::string msg;

    Message em(nick, msg);
    em.type = Message::LOGIN;
    socket.send(em, socket);

    //INICIALIZACION JUEGO SDL
    Environment::init(nick, 640, 480);

    SDL_Renderer* renderer = environment().renderer();

    // Establecer el color de fondo del renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    Scene1* scene = new Scene1(renderer,this);
    spaceCraft1=new SpaceCraft(renderer,this);
    spaceCraft1->setImage("Assets/naves.png", 8, 0, 8, 8);
    spaceCraft1->setPosition(50,50);
    scene->addObject(spaceCraft1);
    spaceCraft2=new SpaceCraft(renderer,this);
    spaceCraft2->setImage("Assets/naves.png", 8, 8, 8, 8);
    spaceCraft2->setPosition(300,50);

    scene->addObject(spaceCraft2);
    scenes_.push(scene);
    
}

void SpaceClient::logout()
{
    std::string msg;

    Message em(nick, msg);
    em.type = Message::LOGOUT;

    socket.send(em, socket);
    
}

void SpaceClient::input_thread()
{
    // //aqui se tendra que hacer el update de sdl renderizar la ventana....
    // while (true)
    // {
    //     // Leer stdin con std::getline
    //     std::string msg;
    //     std::getline(std::cin, msg);

    //     if(msg == "logout") break;
    //     ChatMessage em(nick, msg);

    //     em.type = ChatMessage::MESSAGE;
        
    //     // Enviar al servidor usando socket
    //     socket.send(em, socket);
    // }

    bool salir = false;
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
		scenes_.front()->update();


		environment().clearRenderer({0, 30, 160});

		scenes_.front()->render();
     

		environment().presentRenderer();

		Uint32 frameTime = environment().currRealTime() - startTime;
		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
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

        // Mostrar en pantalla el mensaje de la forma "nick: mensaje"
      //  std::cout << message_.nick << ": " << message_.message << "\n";
     
    }
}

void SpaceClient::sendAction(int action){

    auto act=MessageInputShip::Input::LEFT;
    switch (action)
    {
    case 0://tecla space
        act=MessageInputShip::Input::SPACE;
        break;
    case 2://tecla derecha
      act=MessageInputShip::Input::RIGHT;
      break;
    default:
        break;
    }
    MessageInputShip em( act);
    //mandamos mensaje al servidor
    socket.send(em, socket);
}