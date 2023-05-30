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

    void addEnemyExtreme(Enemy *enemy, EnemyType enemyType);

    virtual void changeDirection() {};

    virtual void shoot() {};

protected:

    float moveTimer = 1.0f;
    float timerForMove = 0.0f;

    int myID = 0;

    SpaceClient *spaceClient;

private:

    std::vector<Enemy*> enemies1;
    std::vector<Enemy*> actualExtremesOfEnemies1;

    int translateY = 5;
    int auxiliarMove = 10;

    float shootTimer = 2.0f;
    float timerForShoot = 0.0f;

};
#endif /*__GAMEOBJECT_H__*/