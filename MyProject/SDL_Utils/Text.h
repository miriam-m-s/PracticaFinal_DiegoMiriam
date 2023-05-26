#ifndef __TEXT_H__
#define __TEXT_H__
#include <SDL.h>
#include <SDL_ttf.h>

class Text{

public:

    Text() {};

    ~Text() {
        SDL_DestroyTexture(texture);
    }

    void setText(SDL_Renderer *renderer_, const char* text){

        renderer = renderer_;
        texture = LoadText(text);

        if (texture == nullptr) {
            std::cout << "No se pudo cargar el texto" << std::endl;
        }

    }

    void setParams(int posx_, int posy_, int textWidth_, int textHeight_){
        posx = posx_;
        posy = posy_;

        textWidth = textWidth_;
        textHeight = textHeight_;
    }

    void Render() {
        if (texture != nullptr) {
            SDL_Rect textRect = {posx, posy, textWidth, textHeight};
            SDL_RenderCopy(renderer, texture, NULL, &textRect);
        }
    }


private:

    SDL_Renderer* renderer;
    SDL_Texture* texture;

    int posx, posy, textWidth, textHeight;

    SDL_Texture* LoadText(const char* text) {

        SDL_Color color = { 255, 255, 255 };
        TTF_Font* font = TTF_OpenFont("Assets/Mario.ttf", 24);
        if (font == NULL) {
            // Manejar el error si no se puede cargar la fuente
            printf("Error al cargar la fuente: %s\n", TTF_GetError());
        }

        SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
        
        if (surface == nullptr) {
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    }

};

#endif