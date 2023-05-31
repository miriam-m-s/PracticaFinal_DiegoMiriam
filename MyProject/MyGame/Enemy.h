#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <vector>
#include <random>

#include"../SDL_Utils/GameObject.h"

class Enemy:public GameObject{
public:

    enum EnemyType
    {
        ENEMY1   = 0,
        ENEMY2 = 1,
        ENEMY3  = 2 
    };

    Enemy(SDL_Renderer* renderer, SpaceClient *spaceClient_); //    
    ~Enemy();

    void setID(int id);

    virtual void update(float deltaTime);

    void addEnemy(Enemy *enemy, EnemyType enemyType);

    void orderShoot(int enemeyType, int enemySelected);

    virtual void changeDirection() {};

    virtual void shoot() {};

    virtual void OnCollision(GameObject *other){};

protected:

    void removeEnemy(Enemy *enemy, EnemyType enemyType);

    float moveTimer = 1.0f;
    float timerForMove = 0.0f;

    int myID = 0;

    SpaceClient *spaceClient;

private:

    std::vector<Enemy*> enemies1;
    std::vector<Enemy*> enemies2;
    std::vector<Enemy*> enemies3;

    int translateY = 5;
    int auxiliarMove = 10;

    float shootTimer = 2.0f;
    float timerForShoot = 0.0f;

    float tranlateX=10;

};
#endif /*__GAMEOBJECT_H__*/