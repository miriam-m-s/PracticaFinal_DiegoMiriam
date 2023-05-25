#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>
#include "Serializable.h"
#include "Socket.h"
class Message: public Serializable
{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t);

    enum MessageType
    {
        LOGIN   = 0,
        MESSAGE = 1,
        LOGOUT  = 2
    };

    Message(){};

    Message(const std::string& n, const std::string& m):nick(n),message(m){};

    void to_bin();

    int from_bin(char * bobj);

    uint8_t type;

    std::string nick;
    std::string message;
};


class MessageSpaceShip: public Serializable
{
public:

    MessageSpaceShip(){};

    MessageSpaceShip(const int posx_, const int posy_, const int posInSpritex_, const int posInSpritey_):
            posx(posx_), posy(posy_), posInSpritex(posInSpritex_), posInSpritey(posInSpritey_){};

    void to_bin();

    int from_bin(char * bobj);

    uint8_t posx, posy, posInSpritex, posInSpritey;
};

