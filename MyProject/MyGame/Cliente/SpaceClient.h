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
class Enemy;
class Bala;
class BackGroundLobby;
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
    void callSceneLobby();
    /**
     *  Envía el mensaje de logout al servidor
     */
    void logout();

    void play();

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
    void sendMessage(int action);
    int getId(){
        return myID;
    }

    void addBullet(Bala *bullet);

    void addGameObjectToScene(GameObject * obj);

private:

    //Socket para comunicar con el servidor
    Socket socket;
    BackGroundLobby *backGround;
    SpaceCraft* spaceCrafts[2];

    // Asignar valores a los el
    int idspacecraft=0;

    //offset entre enemigos
    int enemiesOffset = 5;

    //Nick del usuario
    std::string nick;

    //Id del cliente
    uint8_t myID;

    SDL_Renderer* renderer;

    std::vector<Enemy*> enemies;
    std::vector<Bala*> bullets;
    //escenas del juego
    std::queue<Scene*> scenes_;

    void checkCollisions();
    bool checkCollision(GameObject *obj1, GameObject *obj2);
};

