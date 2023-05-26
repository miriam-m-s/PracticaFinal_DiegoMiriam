#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>

#include "../RedUtils/Serializable.h"
#include "../RedUtils/Socket.h"

struct infoClient{
    int posx, posy;
    int posInSpritex, posInSpritey;
};
//------------------------------------------------------------------------------

class ChatServer
{
public:
    ChatServer(const char * s, const char * p): socket(s, p)
    {
        socket.bind();
    };

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void do_messages();

private:

    void registerClient(Socket* socket_cliente);

    /**
     *  Lista de clientes conectados al servidor de Chat, representados por
     *  su socket
     */
    std::vector<std::unique_ptr<Socket>> clients;

    /**
     * Socket del servidor
     */
    Socket socket;
    infoClient ship1;
    infoClient ship2;
    int idClient = 0;
};


