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
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + 8*sizeof(uint8_t);

    enum MessageType
    {
        LOGIN   = 0,
        MESSAGE = 1,
        LOGOUT  = 2,
        INPUT = 3,
        WAITING = 4,
        READY = 5, 
        SHOOTENEMY = 6,
        COLLISION = 7
    };

    enum Input
    {
        SPACE   = 0,
        LEFT = 1,
        RIGHT  = 2
    };

    Message(){};

    Message(const std::string& n, const std::string& m):nick(n),message(m){};

    void to_bin();

    int from_bin(char * bobj);

    uint8_t type, input, shipMoved, idClient, enemySelected, typeEnemy, indexObj1, indexObj2;

    std::string nick;
    std::string message;
};