/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDLSprite
*/

#ifndef SDLSPRITE_HPP_
#define SDLSPRITE_HPP_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace graphicals {
    class SDLSprite {
        public:
            SDLSprite(const std::string &filepath, SDL_Renderer *renderer, const int x, const int y, const int size);
            ~SDLSprite();

            // Getters
            SDL_Rect getRect() const;
            SDL_Texture *getTexture() const;

        private:
            SDL_Texture *_texture;
            SDL_Rect _rect;
    };
}

#endif /* !SDLSPRITE_HPP_ */
