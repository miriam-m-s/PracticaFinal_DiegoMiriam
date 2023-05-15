#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Image {
public:
    Image(SDL_Renderer* renderer, const std::string& filePath, int x, int y, int width, int height)
        : renderer(renderer), x(x), y(y), width(width), height(height), texture(nullptr) {
        texture = LoadTexture(filePath);
        if (texture == nullptr) {
           // std::cout << "No se pudo cargar la imagen desde " << filePath << std::endl;
        }
    }
    Image()
        : renderer(nullptr), x(0), y(0), width(8), height(8), texture(nullptr) {
    
    }
    void setImage(SDL_Renderer* renderer, const std::string& filePath, int x, int y, int width, int height){
        renderer=renderer;
        x=x;
        y=y;
        width=width; 
        height=height;
         texture=nullptr;
        texture = LoadTexture(filePath);
        // if (texture == nullptr) {
        //     std::cout << "No se pudo cargar la imagen desde " << filePath << std::endl;
        // }
    }
    ~Image() {
        SDL_DestroyTexture(texture);
    }

    void Render() {
        if (texture != nullptr) {
            SDL_Rect clipRect = { x, y, width, height };
            SDL_RenderCopy(renderer, texture, &clipRect, NULL);
        }
    }
    float getTexWidht(){
        return textureWidth;
    }
     float getTexHeight(){
        return textureHeight;
    }
    SDL_Texture* getTexture(){
        return texture;
    }
private:
    SDL_Renderer* renderer;
    int x;
    int y;
    int width;
    int height;
    SDL_Texture* texture;
    float textureWidth;
    float textureHeight;
    SDL_Texture* LoadTexture(const std::string& filePath) {
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (surface == nullptr) {
            std::cout << "AAAAAAAAAAAAANo se pudo cargar la imagen desde " << filePath << ". Error: " << IMG_GetError() << std::endl;
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
         if (texture != nullptr) {
            textureWidth = surface->w;
            textureHeight = surface->h;
             std::cout << "aaaaaaa " << std::endl;
        }
        SDL_FreeSurface(surface);
        return texture;
    }
};