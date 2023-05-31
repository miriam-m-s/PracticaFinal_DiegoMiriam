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
    memcpy(buffer, &indexObj1, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(buffer, &indexObj2, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(buffer, &type, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(buffer, &input, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(buffer, &shipMoved, sizeof(uint8_t));
    buffer += sizeof(uint8_t);
    memcpy(buffer, &idClient, sizeof(uint8_t));
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
    char* buffer = _data; 
    memcpy(&indexObj1, buffer, sizeof(uint8_t)); 
    buffer += sizeof(uint8_t); 
    memcpy(&indexObj2, buffer, sizeof(uint8_t)); 
    buffer += sizeof(uint8_t); 
    memcpy(&type, buffer, sizeof(uint8_t)); 
    buffer += sizeof(uint8_t); 
    memcpy(&input, buffer, sizeof(uint8_t)); 
    buffer += sizeof(uint8_t); 
    memcpy(&shipMoved, buffer, sizeof(uint8_t)); 
    buffer += sizeof(uint8_t); 
    memcpy(&idClient, buffer, sizeof(uint8_t)); 
    buffer += sizeof(uint8_t); 
    char nick_buffer[10] = {0}; 
    memcpy(nick_buffer, buffer, 10* sizeof(char)); 
    nick = std::string(nick_buffer); 
    buffer += 10* sizeof(char); 
    char message_buffer[81] = {0}; 
    memcpy(message_buffer, buffer, 80 * sizeof(char)); 
    message = std::string(message_buffer); 
    
    return 0;

}
