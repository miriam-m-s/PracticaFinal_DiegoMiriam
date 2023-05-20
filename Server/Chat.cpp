#include "Chat.h"
#include"string"
#include"../RedUtils/Message.h"
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void ChatServer::do_messages()
{
    while (true)
    {

        /*
         * NOTA: los clientes están definidos con "smart pointers", es necesario
         * crear un unique_ptr con el objeto socket recibido y usar std::move
         * para añadirlo al vector
         */
        Message mensaje;
        
        //Recibir Mensajes en y en socketfunción del tipo de mensaje
        Socket* socket_cliente=new Socket(socket);
        socket.recv(mensaje, socket_cliente);
        // - LOGIN: Añadir al vectosocketr clients
        // - LOGOUT: Eliminar del vector clients
        // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)
        switch(mensaje.type){
            case Message::LOGIN:{
                std::unique_ptr<Socket>socket1_(socket_cliente);
                clients.push_back(std::move(socket1_));
                std::cout<<"LOGIN DE: "<<mensaje.nick<<"\n";
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
                std::cout<<"LOGOUT DE: "<<mensaje.nick<<"\n";
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
                        socket.send(mensaje, *(*it));
                        std::cout<<"enviando"<<std::endl;
                    } 
                ++it;
                }
                break;
            }
             
        }
      
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

