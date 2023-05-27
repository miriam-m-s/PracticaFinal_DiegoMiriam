#include "Chat.h"
#include"string"
#include"../RedUtils/Message.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
bool exit_ = false;
void handle_interrupt(int) {
   exit_ = true;
}
ChatServer::ChatServer(const char * s, const char * p): socket(s, p)
{
    socket.bind();
     struct sigaction act;
    act.sa_handler = handle_interrupt;
    sigaction(SIGINT, &act, NULL);
}
void ChatServer::registerClient(Socket* socket_cliente){

    if(idClient == 0){      
        ship1.posx = 50;
        ship1.posy = 50;
        ship1.posInSpritex = 8;
        ship1.posInSpritey = 0;
        idClient++;
        
    }

    else{
   
        ship2.posx = 60;
        ship2.posy = 50;
        ship2.posInSpritex = 8;
        ship2.posInSpritey = 8;
        // MessageSpaceShip message(ship1.posx , ship1.posy,ship1.posInSpritex,ship1.posInSpritey);
        // MessageSpaceShip message2(ship2.posx , ship2.posy,ship2.posInSpritex,ship2.posInSpritey);
    }
}

void ChatServer::do_messages()
{
    
    while (exit_)
    {
       
        /*
         * NOTA: los clientes están definidos con "smart pointers", es necesario
         * crear un unique_ptr con el objeto socket recibido y usar std::move
         * para añadirlo al vector
         */
        Message message;
        
        //Recibir Mensajes en y en socketfunción del tipo de mensaje
        Socket* socket_cliente=new Socket(socket);
        socket.recv(message, socket_cliente);
        // - LOGIN: Añadir al vectosocketr clients
        // - LOGOUT: Eliminar del vector clients
        // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)
        switch(message.type){
            case Message::LOGIN:{
                std::unique_ptr<Socket>socket1_(socket_cliente);
                message.idClient = idClient;
                registerClient(socket_cliente);
                clients.push_back(std::move(socket1_));
                socket.send(message, *socket_cliente);
                std::cout<<"LOGIN DE: "<<message.nick<<"\n";
                break;
            }  
            case Message::LOGOUT:{
                std::unique_ptr<Socket>socket_(socket_cliente);
                for(auto it=clients.begin();it!=clients.end();){
                    if(*(*it)==*socket_cliente){
                        clients.erase(it);
                    }
                    else ++it;
                }
                std::cout<<"LOGOUT DE: "<<message.nick<<"\n";
                break;
            }
               
            case Message::MESSAGE:{
                std::cout<<"mandando mensaje"<<std::endl;
                //std::unique_ptr<Socket>socket_(socket_cliente);
                for(auto it=clients.begin();it!=clients.end();){
                    if(*(*it)==*socket_cliente){
                        std::cout<<"no soy yo"<<std::endl;
                    }
                    else{
                        socket.send(message, *(*it));
                        std::cout<<"enviando"<<std::endl;
                    } 
                    ++it;
                }
                break;
            }

            case Message::INPUT:{

                for(auto it=clients.begin();it!=clients.end();){
                    socket.send(message, *(*it));
                    
                    ++it;
                }

                break;
            }
             
        }
      
    }
}



// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

