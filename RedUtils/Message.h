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
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + 4*sizeof(uint8_t);

    enum MessageType
    {
        LOGIN   = 0,
        MESSAGE = 1,
        LOGOUT  = 2,
        INPUT = 3,
        WAITING = 4,
        READY = 5, 
        SHOOTENEMY = 6

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

    uint8_t type, input, shipMoved, idClient, enemySelected, typeEnemy;

    std::string nick;
    std::string message;
};


// class MessageSpaceShip: public Serializable
// {
// public:

//     MessageSpaceShip(){};

//     MessageSpaceShip(const int posx_, const int posy_, const int posInSpritex_, const int posInSpritey_):
//             posx(posx_), posy(posy_), posInSpritex(posInSpritex_), posInSpritey(posInSpritey_){};

//     void to_bin();

//     int from_bin(char * bobj);

//     uint8_t posx, posy, posInSpritex, posInSpritey;
// };

// class MessageInputShip: public Serializable
// {
//    const size_t MESSAGE_SIZE = sizeof(Input)  + sizeof(int);
// public:
//      enum Input:uint8_t
//     {
//         SPACE   = 0,
//         LEFT = 1,
//         RIGHT  = 2
//     };
//     MessageInputShip(){};

//     MessageInputShip(const Input& input, int shipMoved_):
//             input_(input), shipMoved(shipMoved_){};

//     void to_bin();

//     int from_bin(char * bobj);
//     Input input_;
//     // if ship1 moved = 0, if ship2 moved = 1
//     int shipMoved;
// private:
    
// };

// class PackagedShipInfo: public Serializable
// {
//    const size_t MESSAGE_SIZE = sizeof(Message) + sizeof(MessageInputShip);
// public:

//     PackagedShipInfo(){};

//     PackagedShipInfo(Message *message_,  MessageInputShip *messageInputShip_):
//             message(message_), messageInputShip(messageInputShip_){};

//     void to_bin();

//     int from_bin(char * bobj);
    
//     Message *message;
//     MessageInputShip *messageInputShip;

// private:
    
// };

