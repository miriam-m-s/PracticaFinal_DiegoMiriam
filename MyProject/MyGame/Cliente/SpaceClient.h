#include <string>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <memory>
#include<queue>
#include "../../../RedUtils/Serializable.h"
#include "../../../RedUtils/Socket.h"
#include"../../SDL_Utils/Scene.h"
class SpaceCraft;
class SpaceClient
{
public:
    
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    SpaceClient(const char * s, const char * p, const char * n):socket(s, p),
        nick(n){};

    ~SpaceClient(){};

    /**
     *  Envía el mensaje de login al servidor
     */
    void login();

    /**
     *  Envía el mensaje de logout al servidor
     */
    void logout();

    /**
     *  Rutina principal para el Thread de E/S. Lee datos de STDIN (std::getline)
     *  y los envía por red vía el Socket.
     */
    void input_thread();

    /**
     *  Rutina del thread de Red. Recibe datos de la red y los "renderiza"
     *  en STDOUT
     */
    void net_thread();
    void create_Bullet(int id);
    void sendAction(int action, int shipMoved);

private:

    /**
     * Socket para comunicar con el servidor
     */
    Socket socket;

     SpaceCraft* spaceCrafts[2];

    // Asignar valores a los el
    int idspacecraft=0;
    /**
     * Nick del usuario
     */
    std::string nick;
    uint8_t myID;
    //escenas del juego
    std::queue<Scene*> scenes_;
};

