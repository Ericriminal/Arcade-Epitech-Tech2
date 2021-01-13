/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** SDLSprite
*/

#include <iostream>
#include "SDLSprite.hpp"

graphicals::SDLSprite::SDLSprite(const std::string &filepath, SDL_Renderer *renderer,
const int x, const int y, const int size) {
    this->_rect = {x, y, size, size};

    this->_texture = IMG_LoadTexture(renderer, filepath.c_str());
    if (!this->_texture)
        throw;
}

graphicals::SDLSprite::~SDLSprite() {
    SDL_DestroyTexture(this->_texture);
}

SDL_Rect graphicals::SDLSprite::getRect() const {
    return (this->_rect);
}

SDL_Texture *graphicals::SDLSprite::getTexture() const {
    return (this->_texture);
}
