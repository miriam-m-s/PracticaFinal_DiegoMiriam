#ifndef __IMAGE_H__
#define __IMAGE_H__
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
        : renderer(nullptr), x(8), y(0), width(8), height(8), texture(nullptr) {
    
    }
    void setImage(SDL_Renderer* renderer_, const std::string& filePath, int x_, int y_, int width_, int height_){
        renderer=renderer_;
        x=x_;
        y=y_;
        width=width_; 
        height=height_;

        texture = LoadTexture(filePath);
        if (texture == nullptr) {
             std::cout << "No se pudo cargar la imagen desde " << filePath << std::endl;
         }
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
    int getTexWidht(){
        return textureWidth;
    }
     int getTexHeight(){
        return textureHeight;
    }
    int getWidht(){
        return width;
    }
     int getHeight(){
        return height;
    }
     int getX(){
        return x;
    }
     int getY(){
        return y;
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
#endif /*__IMAGE_H__*/