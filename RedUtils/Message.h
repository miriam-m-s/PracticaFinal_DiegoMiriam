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
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + 6*sizeof(uint8_t) + 2*sizeof(int);

    enum MessageType
    {
        LOGIN   = 0,
        MESSAGE = 1,
        LOGOUT  = 2,
        INPUT = 3,
        READY = 4,
        PLAYING = 5, 
        COLLISION = 7,
        MOVEENEMY = 6,
        EJECT = 8
    };

    enum Input
    {
        DOWN   = 0,
        LEFT = 1,
        RIGHT  = 2,
        UP = 3
    };

    Message(){};

    Message(const std::string& n, const std::string& m):nick(n),message(m){};

    void to_bin();

    int from_bin(char * bobj);

    uint8_t type, input, shipMoved, idClient, indexObj1, indexObj2;

    int newPosX, flipOfObj;

    std::string nick;
    std::string message;
};