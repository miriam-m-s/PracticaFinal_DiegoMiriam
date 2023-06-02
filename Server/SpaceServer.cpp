#include "SpaceServer.h"
#include"string"
#include"../RedUtils/Message.h"
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

bool exit_ = false;

void handle_interrupt(int) {
   exit_ = true;
}

SpaceServer::SpaceServer(const char * s, const char * p): socket(s, p)
{
    socket.bind();
     struct sigaction act;
    act.sa_handler = handle_interrupt;
    sigaction(SIGINT, &act, NULL);
}

void SpaceServer::registerClient(Socket* socket_cliente){

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
    }
}

void SpaceServer::do_messages()
{
    
    while (true)
    {
       

        Message message;
        
        Socket* socket_cliente=new Socket(socket);
        socket.recv(message, socket_cliente);
        // - LOGIN: Añadir al vectosocketr clients
        // - LOGOUT: Eliminar del vector clients
        // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)
  
        switch(message.type){
            case Message::LOGIN:{

                if(clients.size() < 2){
                    std::unique_ptr<Socket>socket1_(socket_cliente);
                    message.idClient = clients.size();
                    registerClient(socket_cliente);
                    clients.push_back(std::move(socket1_));
                    socket.send(message, *socket_cliente);
                    std::cout<<"LOGIN DE: "<<message.nick<<"\n";

                    //Los dos clientes estan conectados
                    if(clients.size() == 2){
                        message.type = Message::READY;
                        for(auto it=clients.begin();it!=clients.end();){
                            socket.send(message, *(*it));   
                            ++it;
                        }
                    }
                }

                else{
                    std::cout<<"EXPULSION DE: "<<message.nick<<"\n";
                    message.type = Message::EJECT;
                    socket.send(message, *socket_cliente);  
                }

                break;
            }  

            case Message::PLAYING:{
                message.type = Message::PLAYING;
                for(auto it=clients.begin();it!=clients.end();){
                    socket.send(message, *(*it));   
                    ++it;
                }
                break;
            }

            case Message::LOGOUT:{
                std::unique_ptr<Socket>socket_(socket_cliente);
                message.type = Message::LOGOUT;
                for(auto it=clients.begin();it!=clients.end();){
                    if(*(*it)==*socket_cliente){
                        clients.erase(it);
                    }
                    else { 
                        message.idClient = 0;
                        socket.send(message, *(*it));  
                        ++it;
                    }
                }
                std::cout<<"LOGOUT DE: "<<message.nick<<"\n";
                break;
            }
               
            case Message::MESSAGE:{
                std::cout<<"mandando mensaje"<<std::endl;
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
                if(message.input==0){std::cout<<"shootnsdh\n"  ;  }
                for(auto it=clients.begin();it!=clients.end();){
                    socket.send(message, *(*it));  
                    ++it;
                }

                break;
            }

            case Message::COLLISION:{
                for(auto it=clients.begin();it!=clients.end();){
                    socket.send(message, *(*it));  
                    ++it;
                }

                break;
            }

            case Message::MOVEENEMY:{
                for(auto it=clients.begin();it!=clients.end();){
                    socket.send(message, *(*it));  
                    ++it;
                }

                break;
            }
             
        }
      
    }
}
