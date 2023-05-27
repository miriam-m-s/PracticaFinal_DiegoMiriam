#include <iostream>

class GameManager {
public:
    static GameManager& getInstance() {
        static GameManager instance;
        return instance;
    }
    void initialize() {
        std::cout << "Inicializando el GameManager..." << std::endl;
        // Realizar la inicialización necesaria para el juego
    }
    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    void getWindowHeightAndWidth(int& height, int& width);
   

private:
    GameManager() {}
    ~GameManager() {}
    int m_height;
    int m_width;
};