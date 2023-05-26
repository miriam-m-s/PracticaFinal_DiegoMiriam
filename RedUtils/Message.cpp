#include "Message.h"
#include"string"
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void Message::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);
    //Serializar los campos type, nick y message en el buffer _data
    char* buffer = _data;
    memcpy(buffer, &type, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(buffer, nick.c_str(), sizeof(char)* 10);
    buffer += sizeof(char) * 10;
    memcpy(buffer, message.c_str(), sizeof(char) * 80);
}

int Message::from_bin(char * bobj)
{
    alloc_data(MESSAGE_SIZE); 
    memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE); 
    //Reconstruir la clase usando el buffer _data
     char* buffer = _data; memcpy(&type, buffer, sizeof(uint8_t)); 
     buffer += sizeof(uint8_t); char nick_buffer[10] = {0}; memcpy(nick_buffer, buffer, 10* sizeof(char)); nick = std::string(nick_buffer); buffer += 10* sizeof(char); char message_buffer[81] = {0}; memcpy(message_buffer, buffer, 80 * sizeof(char)); message = std::string(message_buffer); return 0;

}

void MessageSpaceShip::to_bin()
{
    alloc_data(4*sizeof(uint8_t));

    memset(_data, 0, 4*sizeof(uint8_t));
    
    char* buffer = _data;
    memcpy(buffer, &posx, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(buffer, &posy, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(buffer, &posInSpritex, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(buffer, &posInSpritey, sizeof(uint8_t));
}

int MessageSpaceShip::from_bin(char * bobj)
{
    alloc_data(4*sizeof(uint8_t)); 
    memcpy(static_cast<void*>(_data), bobj, 4*sizeof(uint8_t)); 
    //Reconstruir la clase usando el buffer _data
    char* buffer = _data; 
    memcpy(&posx, buffer, sizeof(uint8_t)); 
    buffer += sizeof(uint8_t); 
    memcpy(&posy, buffer, sizeof(uint8_t)); 
    buffer += sizeof(uint8_t); 
    memcpy(&posInSpritex, buffer, sizeof(uint8_t)); 
    buffer += sizeof(uint8_t); 
    memcpy(&posInSpritey, buffer, sizeof(uint8_t)); 
    return 0;

}
void MessageInputShip::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);
    //Serializar los campos type, nick y message en el buffer _data
    char* buffer = _data;
    memcpy(buffer, &input_, sizeof(Input));

    
}

int MessageInputShip::from_bin(char * bobj)
{
    alloc_data(MESSAGE_SIZE); 
    memcpy(static_cast<void*>(_data), bobj, MESSAGE_SIZE); 
    //Reconstruir la clase usando el buffer _data
    char* buffer = _data; 
     memcpy(&input_, buffer, sizeof(Input));
     return 0;
}